#include "qwmainwind.hh"

#include "./ui_qwmainwind.h"
#include "moc_qwmainwind.cpp"

QWMainWind::QWMainWind(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::QWMainWind) {
  ui->setupUi(this);

  IniUi();
  IniSignalSlots();
}

QWMainWind::~QWMainWind() { delete ui; }

void QWMainWind::IniUi() {
  label_status_bar = new QLabel;
  label_status_bar->setText(tr("Current File"));
  ui->statusbar->addWidget(label_status_bar);

  progress_bar = new QProgressBar;
  progress_bar->setMaximumWidth(200);
  progress_bar->setRange(0, 500);
  progress_bar->setValue(ui->textEdit->font().pointSize());
  ui->statusbar->addWidget(progress_bar);

  spin_font_size = new QSpinBox;
  spin_font_size->setRange(10, 50);
  spin_font_size->setMinimumWidth(50);
  spin_font_size->setValue(ui->textEdit->font().pointSize());
  ui->toolBar->addWidget(new QLabel("Font Size"));
  ui->toolBar->addWidget(spin_font_size);

  ui->toolBar->addSeparator();
  ui->toolBar->addWidget(new QLabel(tr("Font")));
  combo_font = new QFontComboBox;
  combo_font->setMaximumWidth(150);
  ui->toolBar->addWidget(combo_font);
}

void QWMainWind::IniSignalSlots() {
  connect(spin_font_size, &QSpinBox::valueChanged, this,
          &QWMainWind::on_spinFontSize_valueCHanged);
  connect(combo_font, &QFontComboBox::currentFontChanged, this,
          &QWMainWind::on_comboFont_currentFontChanged);
}

void QWMainWind::on_actionFontBold_triggered(bool checked) {
  auto fmt = ui->textEdit->currentCharFormat();
  if (checked)
    fmt.setFontWeight(QFont::Bold);
  else
    fmt.setFontWeight(QFont::Normal);

  ui->textEdit->mergeCurrentCharFormat(fmt);
}

void QWMainWind::on_actionFontItalic_triggered(bool checked) {
  auto fmt = ui->textEdit->currentCharFormat();
  if (checked)
    fmt.setFontItalic(checked);
  else
    fmt.setFontItalic(0);
  ui->textEdit->mergeCurrentCharFormat(fmt);
}

void QWMainWind::on_actionFontUnder_triggered(bool checked) {
  auto fmt = ui->textEdit->currentCharFormat();
  if (checked)
    fmt.setFontUnderline(checked);
  else
    fmt.setFontUnderline(0);
  ui->textEdit->mergeCurrentCharFormat(fmt);
}

void QWMainWind::on_textEdit_copyAvailable(bool b) {
  ui->actionCut->setEnabled(b);
  ui->actionCopy->setEnabled(b);
  ui->actionPaste->setEnabled(b);
}

void QWMainWind::on_textEdit_currentCharFormatChanged(
    const QTextCharFormat &format) {
  auto fmt = ui->textEdit->currentCharFormat();
  ui->actionFontBold->setChecked(fmt.font().bold());
  ui->actionFontItalic->setChecked(fmt.fontItalic());
  ui->actionFontUnder->setChecked(fmt.fontUnderline());
  spin_font_size->setValue(fmt.fontPointSize());
  combo_font->setCurrentFont(ui->textEdit->currentFont());
}

void QWMainWind::on_spinFontSize_valueCHanged(int i) {
  QTextCharFormat fmt;
  fmt.setFontPointSize(i);
  ui->textEdit->mergeCurrentCharFormat(fmt);
  progress_bar->setValue(i);
}

void QWMainWind::on_comboFont_currentFontChanged(const QFont &font) {
  QTextCharFormat fmt;
  fmt.setFont(font);
  ui->textEdit->mergeCurrentCharFormat(fmt);
}
