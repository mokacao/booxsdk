#ifndef LIB_DICT_WIDGET_H_
#define LIB_DICT_WIDGET_H_

#include "onyx/base/base.h"
#include "onyx/ui/ui.h"
#include "dictionary_manager.h"
#include "onyx/tts/tts.h"

namespace ui
{

/// The dictionary widget library. It provides a gui frontend
/// for LibDict to enable user to search in dictionary.
class DictWidget : public QDialog
{
    Q_OBJECT

public:
    struct FunctionDescription
    {
        const char * description;
        int index;
    };

private:
    static const int SPACING;
    static const FunctionDescription DICT_FUNC_DESCRIPTION[];

public:
    DictWidget(QWidget *parent, DictionaryManager & dict, tts::TTS *tts = 0);
    ~DictWidget();

public:
    bool ensureVisible(const QRectF & rect, bool update_parent = false);
    bool lookup(const QString &word);

protected:
    virtual void keyReleaseEvent(QKeyEvent *);
    virtual void keyPressEvent(QKeyEvent *);
    virtual bool event(QEvent *);
    void moveEvent(QMoveEvent *e);
    void resizeEvent(QResizeEvent *e);
    void hideEvent(QHideEvent * event);

Q_SIGNALS:
    void keyReleaseSignal(int);
    void closeClicked();

private:
    void createLayout();
    void initBrowser();
    void initDictionaries();
    void launchTimer(bool launch);

    void updateSimilarWordsModel(int count);
    void resetSimilarWordsOffset() { similar_words_offset_ = 0; }
    void updateSimilarWords();

    void updateDictionaryListModel();
    void updateDictionaryList();

    void updateVisibleWidgets();
    bool eventFilter(QObject *obj, QEvent *event);

    void changeInternalState(int);
    int  internalState() { return internal_state_; }

private Q_SLOTS:
    void onTimeout();
    void onItemClicked(const QModelIndex & index);
    void onDetailsClicked(bool);
    void onLookupClicked(bool);
    void onWordListClicked(bool);
    void onDictListClicked(bool);
    void onRetrieveWordClicked(bool);
    void onCloseClicked();
    void moreSimilarWords(bool);

private:
    DictionaryManager&      dict_;
    tts::TTS *tts_;

    QVBoxLayout   content_vbox_;

    QVBoxLayout   big_vbox_;
    QHBoxLayout   top_hbox_;

    OnyxPushButton explanation_button_;
    OnyxPushButton similar_words_button_;
    OnyxPushButton dictionaries_button_;
    OnyxPushButton open_dictionary_tool_button_;

    OnyxTextBrowser  explanation_text_; ///< The lookup result.
    OnyxTreeView similar_words_view_;

    QButtonGroup    button_group_;
    QTextDocument   doc_;
    QString         word_;                  ///< Word currently queried.
    QStringList     similar_words_;
    int             similar_words_offset_;
    QTimer          timer_;                 ///< Timer to update the screen.

    QStandardItemModel similar_words_model_;
    QStandardItemModel dict_list_model_;

    int internal_state_;
    bool update_parent_;

    QLabel func_discription_label_;
};

};  // namespace ui

#endif // LIB_DICT_WIDGET_H_
