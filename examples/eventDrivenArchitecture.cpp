/* Event driven programming , flow of program is determined by external events ,
 UI events from keyboards,mice ,touchscreens

 event generation-> Event queue ->event loop (checks for events)-> callback function

 Example Event driven architecture in C++ without using Qt

    1. Button event is generate
    2. event is place in event queue
    3. Event loop picks up the event
    4. Event Handler processes it

*/

#include <iostream>
#include <queue>

enum class EventType  // describes something happened
{
  ButtonClicked,
  MouseMoved,
  ApplicationQuit
};

struct Event {
  EventType type;
};

std::queue<Event> eventQueue;

void postEvent(Event event)  // event publisher
{
  eventQueue.push(event);
}

//Event handlers
void handleButtonClick(){std::cout<<"Button clicked Handled\n";}

void handleMouseMove() {std::cout<<"Mouse move event handled\n";}

void handleAppliationClose() {std::cout<<"Application Closed\n";}


//EventDispatcher
class EventDispatcher
{
	public:
	bool dispatch(const Event& event)
	{
		switch(event.type)
		{
			case EventType::ButtonClicked:
				handleButtonClick();
				break;
			case EventType::MouseMoved:
				handleMouseMove();
				break;
			case EventType::ApplicationQuit:
				handleAppliationClose();
				return false;
				
		}
		return true;

    }
};

 // Retrives and processes the events.(Consumer)
void eventLoop() 
{
  bool running = true;
  while (running && !eventQueue.empty()) {
    Event currentEvent = eventQueue.front();
    eventQueue.pop();

    EventDispatcher dispatcher;
    dispatcher.dispatch(currentEvent);
    
  }
}


int main() {
  postEvent({EventType::ButtonClicked});
  postEvent({EventType::MouseMoved});
  postEvent({EventType::MouseMoved});

  postEvent({EventType::ApplicationQuit});
  eventLoop();
  return 0;
}
