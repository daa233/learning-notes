import cv2


cap = cv2.VideoCapture(0)

# define the codec and create VideoWriter object
fourcc = cv2.VideoWriter_fourcc(*"XVID")
fps = 20
frame_size = (1280, 720)  # (width, height)
is_color = True
out = cv2.VideoWriter("output.avi", fourcc, fps, frame_size, is_color)

while cap.isOpened():
    # capture frame-by-frame
    ret, frame = cap.read()

    # if frame is read correctly ret is True
    if not ret:
        print("Can't receive frame (stream end?). Exiting ...")
        break

    # flip the 2D array frame vertical (flipCode = 0)
    frame = cv2.flip(frame, flipCode=0)

    # write the flipped frame
    frame_height, frame_width, _ = frame.shape
    assert (frame_width, frame_height) == frame_size, "frame.shape {} not equals the frame_size {}".format(
        (frame_width, frame_height), frame_size
    )
    # the frame's shape must be the same with the VideoWriter.frameSize
    out.write(frame)

    # display the resulting frame
    cv2.imshow("frame", frame)
    if cv2.waitKey(1) == ord("q"):
        break

# release everything if job is finished
cap.release()
out.release()
cv2.destroyAllWindows()
