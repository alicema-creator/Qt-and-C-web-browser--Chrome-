#include "MainWindow.h"

#include "QUrl"
#include <iostream>
#include<string>
#include<QKeyEvent>



using namespace std;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	styleRun();

	QObject::connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(openWeb()));
	
	QObject::connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(on_pushButton_reload_clicked()));
	QObject::connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(on_pushButton_forward_clicked()));
	QObject::connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(on_pushButton_back_clicked()));
	QObject::connect(ui.pushButton_5, SIGNAL(clicked()), this, SLOT(zoomInView()));
	QObject::connect(ui.pushButton_6, SIGNAL(clicked()), this, SLOT(zoomOutView()));

	ui.pushButton_5->hide();
	ui.pushButton_6->hide();



	ui.mainToolBar->hide();
	ui.frame->setStyleSheet("QFrame{border-width: 0px;border-style: none;}");
	ui.frame_2->setStyleSheet("QFrame{border-width: 0px;border-style: none;}");


	ui.tabWidget->setCurrentIndex(0);

	
}


//������ʽ��
void MainWindow::styleRun()
{
	//��ҳ��������
	QFontDatabase fontDataBase;
	QWebEngineSettings* defaultSettings = QWebEngineSettings::globalSettings();
	QFont standardFont = fontDataBase.font("Microsoft Yahei", "", 12);
	defaultSettings->setFontFamily(QWebEngineSettings::StandardFont, standardFont.family());
	//��ҳ�������ý���

	//������ʽ��
	QString cssStr = "./style/style_pushButton2.css";
	QString css;
	QFile file(cssStr);


	//������ʽ�����

	//���������ڱ�����ɫ
	//QPalette palette;
	//palette.setColor(QPalette::Window, QColor(145, 247, 247));
	//this->setPalette(palette);
	//���������ڱ�����ɫ����

	ui.statusBar->showMessage(QStringLiteral("״̬������ʾ��Ϣ"), 0);//һֱ��ʾ
	QPalette palette2;
	palette2.setColor(QPalette::Window, Qt::red);
	ui.statusBar->setPalette(palette2);

	//ui.statusBar->setStyleSheet("style_pushButton2.css"); //��������

	//�ؼ��������ڼ��
	//ui.gridLayout_3->setMargin(0);

}

//������ҳ
void MainWindow::openWeb()
{
	////�رջ���
	//QWebEngineSettings* webEngineSettings = ui.webEngineView->settings();
	//webEngineSettings->setAttribute(QWebEngineSettings::LocalStorageEnabled, false); //�رջ���
	////�رջ������

	QString webAdd = ui.lineEdit->text();
	string webAddS= webAdd.toLocal8Bit();
	cout << "webAddS: " << webAddS<<endl;
	string httpS = "https://";
	string http = "http://";
	//cout << "httpS: " << httpS << endl;

	string::size_type idxS;
	string::size_type idx;

	//ui.webEngineView->load(QUrl("https://www.baidu.com/"));
	idxS = webAddS.find(httpS);  //��a�в���b.
	idx = webAddS.find(http);  //��a�в���b.
	cout << "idxS: " << idxS << endl;



	else if (idx == 0)		//�����ڡ�
	{
		cout << " found http://\n";
		ui.webEngineView->load(QUrl(webAdd));
	}		
	else		//�����ڡ�
	{
		cout << " not found http:// or http://\n";
		ui.webEngineView->load(QUrl("https://" + webAdd));
		//ui.webEngineView->load(QUrl("http://www.baidu.com"));
	}


		

	// ������ҳ���ű�������Χ��0.25-5��Ĭ��1
	ui.webEngineView->setZoomFactor(1.5);

	// �����ͣ��ҳ��������Ӵ�ӡ����ҳ��ַ
	QObject::connect(ui.webEngineView, &QWebEngineView::loadFinished, [this](bool) {
		QWebEnginePage* page = ui.webEngineView->page();
		if (page) {
			QObject::connect(page, &QWebEnginePage::linkHovered, this, &MainWindow::handleLinkClicked);
		}
	});







	// �����ͣ��ҳ��������Ӵ�ӡ����ҳ��ַ-���Ҳ����
	//QObject::connect(ui.webEngineView->page(), &QWebEnginePage::linkHovered, [this]() {
	//	qDebug() << "clicked22";
	//	});

	// �����ͣ��ҳ��������Ӵ�ӡ����ҳ��ַ-�������Ҳ����
	//QObject::connect(ui.webEngineView->page(), &QWebEnginePage::action, [this](const QVariant& variant) {
	//	if (variant.canConvert<QWebEnginePage::WebAction>() && variant.value<QWebEnginePage::WebAction>() == QWebEnginePage::OpenLinkInNewTab) {
	//		QWebEnginePage* page = qobject_cast<QWebEnginePage*>(sender());
	//		if (page) {
	//			QUrl url = page->requestedUrl();
	//			cout << "Link clicked2: " << url.toString().toStdString() << endl;
	//			cout << "click" << endl; // ��Ӵ�ӡ���
	//		}
	//	}
	//	});




	//����Ҽ����view page source�鿴Դ��
	//ui.webEngineView->pageAction(QWebEnginePage::ViewSource)->setText(QStringLiteral("�鿴Դ��"));
	QAction* viewSourceAction = ui.webEngineView->pageAction(QWebEnginePage::ViewSource);
	if (viewSourceAction)
	{
		viewSourceAction->setText(QStringLiteral("�鿴Դ��"));
		connect(viewSourceAction, &QAction::triggered, [=]() {
			qDebug() << "view page source clicked!";
			});
	}

	// ��ȡ�����������

	//����Ҽ����open link in new tab���µ�tab
	QAction* openLinkInNewTabAction = ui.webEngineView->pageAction(QWebEnginePage::OpenLinkInNewTab);
	if (openLinkInNewTabAction)
	{
		//openLinkInNewTabAction->setText(QStringLiteral("���±�ǩҳ�д�����"));
		connect(openLinkInNewTabAction, &QAction::triggered, [=]() {
			qDebug() << "open link in new tab clicked!";




		

			//ui.webEngineView_2->setUrl(clickedLink);
			ui.webEngineView_2->load(QUrl("http://www.baidu.com"));

			ui.tabWidget->setCurrentIndex(1);

		});
	}




}






// �����ͣ��ҳ��������Ӵ�ӡ����ҳ��ַ
void MainWindow::handleLinkClicked(const QUrl& url)
{
	cout << "Link clicked: " << url.toString().toStdString() << endl;

	/*QString urlT;*/
	
	//if (!url.isEmpty()) {
	//	
	//	urlT = url.toString(); // ��url���ַ�����ʾ��ֵ��aa
	//	cout << "urlT: " << urlT.toStdString() << endl;
	//	// ������ִ����Ĳ�������Ϊ url ��Ϊ��
	//}


	////ui.webEngineView->load(QUrl(url.toString()));
	////����Ҽ����open link in new tab���µ�tab
	//QAction* openLinkInNewTabAction = ui.webEngineView->pageAction(QWebEnginePage::OpenLinkInNewTab);
	//if (openLinkInNewTabAction)
	//{
	//	//openLinkInNewTabAction->setText(QStringLiteral("���±�ǩҳ�д�����"));
	//	connect(openLinkInNewTabAction, &QAction::triggered, [=]() {
	//		qDebug() << "open link in new tab clicked!";
	//		//ui.webEngineView_2->load(QUrl("http://www.baidu.com"));
	//		cout << "urlT2: " << urlT.toStdString() << endl;
	//		ui.webEngineView_2->load(QUrl(urlT));
	//		ui.tabWidget->setCurrentIndex(1);

	//		});
	//}
}



//����-��ӡ��ui.webEngineView�������г������ӵ�ַ
void MainWindow::on_pushButton_7_clicked()
{
	cout << "on_pushButton_7_clicked" << endl;

	// ��ȡ��ǰҳ���QWebEnginePage����
	QWebEnginePage* page = ui.webEngineView->page();
	if (page) {
		// ִ��JavaScript���룬��ȡҳ���еĳ�����
		page->runJavaScript("Array.from(document.getElementsByTagName('a')).map(a => a.href);",
			[this](const QVariant& result) {
				if (result.canConvert<QStringList>()) {
					QStringList links = result.toStringList();
					for (const QString& link : links) {
						qDebug() << "Link: " << link;
					}
				}
			});
	}




}

//����
void MainWindow::on_pushButton_back_clicked()
{
	ui.webEngineView->back();
}

//��ǰ
void MainWindow::on_pushButton_forward_clicked()
{
	ui.webEngineView->forward();
}

//ˢ��
void MainWindow::on_pushButton_reload_clicked()
{
	ui.webEngineView->reload();
}

//�鿴page source
void MainWindow::on_pushButton_8_clicked()
{

	qDebug() << "doProcessShowSourceCode";
	//ui.webEngineView->page()->load(QUrl("http://www.baidu.com"));
	ui.webEngineView->load(QUrl("http://www.baidu.com"));
	//ui.webEngineView->pageAction(QWebEnginePage::ViewSource)->setText(QStringLiteral("�鿴Դ��"));

	QAction* viewSourceAction = ui.webEngineView->pageAction(QWebEnginePage::ViewSource);
	if (viewSourceAction)
	{
		viewSourceAction->setText(QStringLiteral("�鿴Դ��"));
		connect(viewSourceAction, &QAction::triggered, [=]() {
			qDebug() << "�鿴Դ�� clicked!";
			});
	}

}




//����̻س�����С���̻س����󶨰�ť
void MainWindow::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Return) {
		cout << "aa" << endl;
		openWeb();
	}
	else if (event->key() == Qt::Key_Return) {
		cout << "aa" << endl;
		openWeb();
	}
}

double ii = 0.1;
void MainWindow::zoomInView()
{
	ii = ii - 0.01;
	cout << ii << endl;
	ui.webEngineView->setZoomFactor(ii);
	ui.webEngineView->load(QUrl("https://www.baidu.com"));

}

void MainWindow::zoomOutView()
{
	ii = ii + 0.01;
	cout << ii << endl;
	ui.webEngineView->setZoomFactor(ii);
	ui.webEngineView->load(QUrl("https://www.baidu.com"));

}