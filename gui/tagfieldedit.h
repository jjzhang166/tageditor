#ifndef QTGUI_TAGFIELDLINEEDIT_H
#define QTGUI_TAGFIELDLINEEDIT_H

#include "./previousvaluehandling.h"

#include <c++utilities/application/global.h>

#include <QPair>
#include <QWidget>

QT_FORWARD_DECLARE_CLASS(QVBoxLayout)
QT_FORWARD_DECLARE_CLASS(QLabel)

namespace Media {
class TagValue;
class Tag;
DECLARE_ENUM_CLASS(KnownField, unsigned int);
DECLARE_ENUM_CLASS(TagDataType, unsigned int);
DECLARE_ENUM_CLASS(TagTextEncoding, unsigned int);
}

namespace Widgets {
class ButtonOverlay;
class ClearLineEdit;
class ClearComboBox;
class ClearSpinBox;
class ClearPlainTextEdit;
class IconButton;
}

namespace QtGui {

class PicturePreviewSelection;

class TagFieldEdit : public QWidget
{
    Q_OBJECT

public:
    explicit TagFieldEdit(const QList<Media::Tag *> &tags, Media::KnownField field, QWidget *parent = nullptr);

    const QList<Media::Tag *> &tags() const;
    Media::KnownField field() const;
    void setTagField(const QList<Media::Tag *> &tags, Media::KnownField field, PreviousValueHandling previousValueHandling = PreviousValueHandling::Clear, bool preventUiUpdate = false);
    Media::TagValue value(Media::TagTextEncoding encoding, bool includeDescription) const;
    bool setValue(const Media::TagValue &value, PreviousValueHandling previousValueHandling = PreviousValueHandling::Clear);
    bool hasDescription() const;
    bool canApply(Media::KnownField field) const;

public slots:
    void clear();
    void apply();
    void restore();
    void setCoverButtonsHidden(bool hideCoverButtons);

signals:
    void returnPressed();

protected:
    virtual bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void handleRestoreButtonClicked();
    void handleRestoreButtonDestroyed(QObject *obj = nullptr);

private:
    Media::TagDataType determineDataType();
    void setupUi();
    Widgets::ClearLineEdit *setupLineEdit();
    Widgets::ClearPlainTextEdit *setupPlainTextEdit();
    Widgets::ClearComboBox *setupGenreComboBox();
    Widgets::ClearSpinBox *setupSpinBox();
    QPair<Widgets::ClearSpinBox *, Widgets::ClearSpinBox *> &setupPositionInSetSpinBoxes();
    PicturePreviewSelection *setupPictureSelection();
    QWidget *setupFileSelection();
    Widgets::ClearLineEdit *setupDescriptionLineEdit();
    QLabel *setupTypeNotSupportedLabel();
    void updateValue(PreviousValueHandling previousValueHandling = PreviousValueHandling::Clear);
    void updateValue(Media::Tag *tag, PreviousValueHandling previousValueHandling = PreviousValueHandling::Clear);
    void updateValue(const Media::TagValue &value, PreviousValueHandling previousValueHandling = PreviousValueHandling::Clear, bool resetRestoreButton = true);
    Widgets::IconButton *setupRestoreButton();
    void showRestoreButton();
    void applyAutoCorrection(QString &textValue);
    void concretizePreviousValueHandling(PreviousValueHandling &previousValueHandling);

    QVBoxLayout *m_layout;
    const QList<Media::Tag *> *m_tags;
    Media::KnownField m_field;
    Media::TagDataType m_dataType;
    QList<QWidget *> m_widgets;
    Widgets::ClearLineEdit *m_lineEdit;
    Widgets::ClearComboBox *m_comboBox;
    QPair<Widgets::ClearSpinBox *, Widgets::ClearSpinBox *> m_spinBoxes;
    PicturePreviewSelection *m_pictureSelection;
    Widgets::ClearPlainTextEdit *m_plainTextEdit;
    Widgets::ClearLineEdit *m_descriptionLineEdit;
    Widgets::IconButton *m_restoreButton;

};

inline const QList<Media::Tag *> &TagFieldEdit::tags() const
{
    return *m_tags;
}

inline Media::KnownField TagFieldEdit::field() const
{
    return m_field;
}

}

#endif // QTGUI_TAGFIELDLINEEDIT_H
