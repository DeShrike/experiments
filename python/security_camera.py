import cv2
import time
import datetime

def Main():
    detection = False
    detection_stopped_time = None
    timer_started = False
    SECOND_TO_RECORD_AFTER_DETECTION = 5

    capture = cv2.VideoCapture(0)
    frame_size = (int(capture.get(3)), int(capture.get(4)))
    fourcc = cv2.VideoWriter_fourcc(*"mp4v")

    filename = None
    outstream = None

    face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + "haarcascade_frontalface_default.xml")
    body_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + "haarcascade_fullbody.xml")
    while True:
        _, frame = capture.read()

        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        faces = face_cascade.detectMultiScale(gray, 1.3, 10)
        bodies = body_cascade.detectMultiScale(gray, 1.3, 5)

        for (x, y, width, height) in bodies:
            cv2.rectangle(frame, (x, y), (x + width, y + height), (255, 0, 0), 3)

        for (x, y, width, height) in faces:
            cv2.rectangle(frame, (x, y), (x + width, y + height), (255, 0, 0), 3)

        if len(faces) + len(bodies) > 0:
            if detection:
                timer_started = False
            else:
                detection = True
                current_time = datetime.datetime.now().strftime("%Y-%m-%d-%H-%M-%S")
                filename = f"video-{current_time}.mp4"
                if outstream is not None:
                    outstream.release()
                    outstream = None
                outstream = cv2.VideoWriter(filename, fourcc, 20, frame_size)
                print(f"Started Recording {filename}")
        elif detection:
            if timer_started:
                if time.time() - detection_stopped_time > SECOND_TO_RECORD_AFTER_DETECTION:
                    detection = False
                    timer_started = False
                    outstream.release()
                    outstream = None
                    print(f"Stopped Recording {filename}")
            else:
                timer_started = True
                detection_stopped_time = time.time()

        if detection:
            outstream.write(frame)

        cv2.imshow("Camera", frame)

        if cv2.waitKey(1) == ord("q"):
            break

    if outstream is not None:
        outstream.release()
    capture.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    Main()
