#include "menu.h"

Menu::Menu(Window *parent, std::unique_ptr<Executor> controller, std::shared_ptr<IDocument> document, QTextEdit *textEdit)
{
    this->parent = parent;
    this->document = document;
    this->controller = std::move(controller);
    this->textEdit = textEdit;

    createActions();
    connectActions();
    createMenus();
}

void Menu::createMenus()
{
    mnFile = new QMenu("File");
    mnEdit = new QMenu("Edit");

    mnFormat = new QMenu("Format");
    mnFormatText = new QMenu("Text");
    mnFormatAlignment = new QMenu("Alingment");
    mnFormatLineSpacing = new QMenu("Line spacing");

    mnFile->addAction(actFileOpen);
    mnFile->addAction(actFileCreate);
    mnFile->addAction(actFileSave);
    mnFile->addAction(actFileSaveAs);
    mnFile->addAction(actFileExit);

    mnEdit->addAction(actEditCopy);
    mnEdit->addAction(actEditCut);
    mnEdit->addAction(actEditPaste);
    mnEdit->addAction(actEditCancel);
    mnEdit->addAction(actEditRepeat);

    mnFormat->addMenu(mnFormatText);
    mnFormat->addMenu(mnFormatAlignment);
    mnFormat->addMenu(mnFormatLineSpacing);

    mnFormatText->addAction(actFormatTextBold);
    mnFormatText->addAction(actFormatTextItalics);
    mnFormatText->addAction(actFormatTextUnderlined);

    mnFormatAlignment->addAction(actFormatAlingmentCenter);
    mnFormatAlignment->addAction(actFormatAlingmentLeft);
    mnFormatAlignment->addAction(actFormatAlingmentRight);
    mnFormatAlignment->addAction(actFormatAlingmentWidth);

    menuBar()->addMenu(mnFile);
    menuBar()->addMenu(mnEdit);
    menuBar()->addMenu(mnFormat);
    parent->setMenuBar(this->menuBar());
}

void Menu::createActions()
{
    actFileOpen = new QAction("Open");
    actFileCreate = new QAction("Create");
    actFileSave = new QAction("Save");
    actFileSaveAs = new QAction("Save as");
    actFileExit = new QAction("Exit");

    actEditCopy = new QAction("Copy");
    actEditCut = new QAction("Cut");
    actEditPaste = new QAction("Paste");
    actEditCancel = new QAction("Cancel");
    actEditRepeat = new QAction("Repeat");

    actFormatTextBold = new QAction("Bold");
    actFormatTextItalics = new QAction("Italics");
    actFormatTextUnderlined = new QAction("Underlined");

    actFormatAlingmentCenter = new QAction("Center");
    actFormatAlingmentLeft = new QAction("Left");
    actFormatAlingmentRight = new QAction("Right");
    actFormatAlingmentWidth = new QAction("Width");
}


void Menu::connectActions()
{
    connect(actFileOpen, SIGNAL(triggered()), this, SLOT(onActFileOpenTriggered()));
    connect(actFileSave, SIGNAL(triggered()), this, SLOT(onActFileSaveTriggered()));
    connect(actEditCopy, SIGNAL(triggered()), this, SLOT(onActEditCopyTriggered()));
    connect(actEditPaste, SIGNAL(triggered()), this, SLOT(onActEditPasteTriggered()));
    connect(actEditCancel, SIGNAL(triggered()), this, SLOT(onActEditCancelTriggered()));
    connect(actEditRepeat, SIGNAL(triggered()), this, SLOT(onActEditRepeatTriggered()));
}


