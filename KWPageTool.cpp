/*
 *  Copyright (C) 2011 Jignesh Kakadiya <jigneshhk1992@gmail.com>
 *  
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
*/

//pagetool includes
#include "KWPageToolWidget.h"
#include "KWPageTool.h"
#include "frames/KWTextFrameSet.h"

//words includes
#include "KWDocument.h"
#include "KWCanvas.h"

//Qt includes
#include <QList>
#include <QPainter>

//calligra includes
#include <KoTextEditor.h>
#include <KoTextEditor.h>
#include <KoPointerEvent.h>
#include <KoViewConverter.h>
#include <KoTextDocument.h>
#include <KoCanvasBase.h>
#include <KoCanvasController.h>



KWPageTool::KWPageTool( KoCanvasBase *canvas )
    : KoToolBase( canvas ),
    m_widget(0)
{
    KWCanvas *w_canvas = dynamic_cast<KWCanvas*>(canvas);
    m_canvas = w_canvas;
    Q_UNUSED( canvas );
}

KWPageTool::~KWPageTool()
{
}

void KWPageTool::paint( QPainter &painter, const KoViewConverter &converter)
{
    Q_UNUSED( painter );
    Q_UNUSED( converter );
}

void KWPageTool::activate(ToolActivation toolActivation, const QSet<KoShape*> &shapes)
{
    useCursor(Qt::ArrowCursor);
    repaintDecorations();
    Q_UNUSED(toolActivation);
    Q_UNUSED(shapes);
}

void KWPageTool::mousePressEvent( KoPointerEvent *event )
{
    event->ignore();
}

void KWPageTool::mouseMoveEvent( KoPointerEvent *event )
{
    Q_UNUSED( event );
}

void KWPageTool::mouseReleaseEvent( KoPointerEvent *event )
{
    Q_UNUSED( event );
}

void KWPageTool::insertPageBreak()
{
    KoTextEditor *editor = KoTextEditor::getTextEditorFromCanvas(m_canvas);
    if (editor) {
        // this means we have the text tool selected right now.
        editor->insertFrameBreak();
    } else if (m_document->mainFrameSet()) { 
        // lets just add one to the main text frameset
        KoTextDocument doc(m_document->mainFrameSet()->document());
        doc.textEditor()->insertFrameBreak();
      }
}

//returns word canvas
KWCanvas *KWPageTool::getCanvas() const
{
    return m_canvas;
}

KWDocument *KWPageTool::getDocument() const
{
    return m_canvas->document();
}

QList<QWidget *> KWPageTool::createOptionWidgets()
{
    QList< QWidget* > widgets;
    m_widget = new KWPageToolWidget();
    m_widget->setWindowTitle(i18n(""));

    //signal emmited from pagebreakbutton
    connect (m_widget, SIGNAL(pageBreakClicked()), this,
             SLOT(insertPageBreak()));

    widgets.append(m_widget);
    return widgets;
}

#include "KWPageTool.moc"


