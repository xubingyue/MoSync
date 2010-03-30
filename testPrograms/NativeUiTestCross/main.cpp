#include <ma.h>
#include "Frame.h"
#include "Button.h"
#include "Edit.h"
#include "Label.h"
#include "Manager.h"
#include "Layout.h"
#include "MenuItem.h"
#include "Parser.h"
#include "MAHeaders.h"


class Main : public ActionListener {
private:
	Frame *frame;
	Frame *frame2;
	Parser *parser;
	Button *button;
public:
	Main() {
		frame = NULL;
		frame2 = NULL;
		parser = NULL;
		button = NULL;

		frame = new Frame(1);
		Manager::Instance().addWidget(frame);
		frame->addActionListener(this);
	}

	Main(const Main & m) {
		frame=m.frame;
		frame2=m.frame2;
		parser=m.parser;
		button=m.button;
	}

	~Main() {
		//delete(button);
		delete(frame);
		delete(frame2);
		delete(parser);
	}

	void onCreate (int id) {
		if(id==frame->getId()) {

			parser = new Parser(MAIN_LAYOUT, frame);


			button = (Button *) Manager::Instance().findById(32);
			button->addActionListener(this);
/*
			button = new Button("New frame");
			Manager::Instance().addWidget(button);

			button2 = new Button("I am a button");
			Manager::Instance().addWidget(button2);

			edit = new Edit("I am an Edit");
			Manager::Instance().addWidget(edit);

			label = new Label("I am a Label");
			Manager::Instance().addWidget(label);

			l = new Layout(frame);
			l->addWidget(button);
			l->addWidget(button2);
			l->addWidget(edit);
			l->addWidget(label);
			l->build();

			button->addActionListener(this);
			button2->addActionListener(this);

			item = new MenuItem("New frame", frame);
			Manager::Instance().addWidget(item);
			item->addActionListener(this);

			item2 = new MenuItem("Useless", frame);
			Manager::Instance().addWidget(item2);
			item2->addActionListener(this);
*/
		}
	}
	void onClick (int id) {
		if(id==32) {
			frame2 = new Frame(2);
			Manager::Instance().addWidget(frame2);
			frame2->addActionListener(this);
		}
	/*	if(id==item->getId()) {
			frame2 = new Frame(2);
			Manager::Instance().addWidget(frame2);
			frame2->addActionListener(this);
		}*/
	}

};

extern "C" int MAMain() {

	Main main = Main();
	// Handle events
	MAEvent event;
	while(1) {
		while(maGetEvent(&event)) {
			if(event.type==EVENT_TYPE_NATIVE_UI_MSG) {
				Manager::Instance().dispatch( event );
			}
		}
	}
	return 0;
}
