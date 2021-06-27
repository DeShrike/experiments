class EventManager():

    __instance = None

    RefreshEvent = "Refresh"
    ClearEvent = "Clear"

    def __init__(self):
        if EventManager.__instance is not None:
            raise Exeption("Already instanciated")

        self.events = {}

        EventManager.__instance = self

    @staticmethod
    def current():
        if EventManager.__instance == None:
            EventManager()
        return EventManager.__instance

    @staticmethod
    def subscribe(event:str, callback):
        if EventManager.__instance == None:
            EventManager()

        if event not in EventManager.__instance.events:
            EventManager.__instance.events[event] = [ callback ]
        else:
            EventManager.__instance.events[event].append(callback)

    @staticmethod
    def fire(event:str):
        if event not in EventManager.__instance.events:
            return
        for cb in EventManager.__instance.events[event]:
            cb(1)

def handler(data):
    print("handler", data)

def handler2(data):
    print("handler2", data)

EventManager.subscribe(EventManager.RefreshEvent, handler)
EventManager.subscribe(EventManager.RefreshEvent, handler2)

EventManager.fire(EventManager.RefreshEvent)
