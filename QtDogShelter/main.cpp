#include <QtWidgets/QApplication>
#include "test.h"
#include "repo_csv.h"
#include "service.h"
#include "admin_gui.h"
#include "user_gui.h"

/* Lab 14 - Model/View */
#include "dogs_table_model.h"
#include "dogs_view_widget.h"

//#define TESTING

int main(int argc, char *argv[])
{
#ifdef TESTING
	test_all();
#endif
	QApplication a(argc, argv);

	CSVRepo r("db.csv");

	// ue must know r, because it passes a reference to r to all undo/redo objects
	UndoEngine ue(r);
	// r must know ue so that it can put operations on the undo stack
	r.set_undo(&ue);
	// ue is passed to service so that we gain access to it in UI: undo-button-->service-->ue.undo()
	Service s(r, ue);
	
	DogsTableModel* table_model = new DogsTableModel{ r };
	QSortFilterProxyModel* sort_model = new QSortFilterProxyModel{};
	sort_model->setSourceModel(table_model);

	DogsViewWidget dogs_view{ r, sort_model };
	dogs_view.setWindowTitle("Model/View Dogs");
	dogs_view.show();

	//AdminGUI ui(s); ui.show();
	UserGUI ui(s); ui.show();

	
	int ret = a.exec();
	r.save();

	return ret;
}