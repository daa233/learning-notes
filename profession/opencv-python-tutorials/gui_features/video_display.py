import cv2


cap = cv2.VideoCapture(0)
if not cap.isOpened():
    print("Cannot open camera")
    exit()

while True:
    # capture frame-by-frame
    ret, frame = cap.read()

    # if frame is read correctly ret is True
    if not ret:
        print("Can't receive frame (stream end?). Exiting ...")
        break

    # custom operation on the frame, convert to gray here
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # display the resulting frame
    cv2.imshow("frame", gray)
    if cv2.waitKey(1) == ord("q"):
        break

# when everything done, release the capture
cap.release()
cv2.destroyAllWindows()
