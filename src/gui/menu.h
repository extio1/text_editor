#ifndef MENU_H_
#define MENU_H_

#include "window.h"

#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QMainWindow>
#include <QAction>

class Menu : public QMainWindow
{
Q_OBJECT
public:
    Menu(Window *parent, std::unique_ptr<Executor> controller = nullptr, std::shared_ptr<IDocument> document = nullptr, QTextEdit *textEdit = nullptr);

private slots:
    void onActFileOpenTriggered();
    void onActFileSaveTriggered();
    void onActEditCopyTriggered();
    void onActEditPasteTriggered();
    void onActEditCancelTriggered();   
    void onActEditRepeatTriggered();

private:
    void createMenus();
    void createActions();
    void connectActions();

    std::unique_ptr<Executor> controller;
    std::shared_ptr<IDocument> document;

    QTextEdit *textEdit;

    Window *parent;
    QMenu *mnFile;
    QMenu *mnEdit;

    QMenu *mnFormat;
    QMenu *mnFormatText;
    QMenu *mnFormatAlignment;
    QMenu *mnFormatLineSpacing;

    QAction *actFileOpen;
    QAction *actFileSave;
    QAction *actFileSaveAs;
    QAction *actFileExit;
    QAction *actFileCreate;
    QAction *actEditCut;
    QAction *actEditPaste;
    QAction *actEditCopy;
    QAction *actEditCancel;
    QAction *actEditRepeat;

    QAction *actFormatTextBold;
    QAction *actFormatTextItalics;
    QAction *actFormatTextUnderlined;
    QAction *actFormatAlingmentCenter;
    QAction *actFormatAlingmentLeft;
    QAction *actFormatAlingmentRight;
    QAction *actFormatAlingmentWidth;
};

#endif // MENU_H_
