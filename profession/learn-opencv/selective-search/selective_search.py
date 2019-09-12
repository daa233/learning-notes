#!/usr/bin/env python
'''
Usage:
    ./ssearch.py input_image (f|q)
    f=fast, q=quality
Use "l" to display less rects, 'm' to display more rects, "q" to quit.
'''

import sys
import cv2

if __name__ == '__main__':
    # If image path and f/q is not passed as command line arguments,
    # quit and display help message
    if len(sys.argv) < 3:
        print(__doc__)
        sys.exit(1)
    
    # speed-up using multithreads
    cv2.setUseOptimized(True)
    cv2.setNumThreads(4)

    im = cv2.imread(sys.argv[1])    # read image
    # resize image
    new_h = 200
    new_w = int(im.shape[1]*200./im.shape[0])
    im = cv2.resize(im, (new_w, new_h))

    # create selective search segmentation object
    ss = cv2.ximgproc.segmentation.createSelectiveSearchSegmentation()
    # set input image for selective search
    ss.setBaseImage(im)
    
    # switch to fast but low recall selective search method
    if (sys.argv[2] == 'f'):
        ss.switchToSelectiveSearchFast()
    # switch to high recall but slow selective search method
    elif (sys.argv[2] == 'q'):
        ss.switchToSelectiveSearchQuality()
    else:
        print(__doc__)
        sys.exit(1)
    
    # run selective search
    rects = ss.process()
    print("Total number of region proposals: {}".format(len(rects)))

    # number of region proposals to show
    num_show_rects = 100
    # increament to increase/decrease region proposals to show
    increment = 50

    while True:
        im_out = im.copy()

        for i, rect in enumerate(rects):
            if (i < num_show_rects):
                x, y, w, h = rect
                cv2.rectangle(im_out, (x, y), (x+w, y+h),
                              (0, 255, 0), 1, cv2.LINE_AA)
            else:
                break
        
        # show output
        cv2.imshow("Output", im_out)

        # record key press
        k = cv2.waitKey(0) & 0xFF

        if k == 109:
            # press 'm' to show more region proposals
            num_show_rects += increment
        elif k == 108 and num_show_rects > increment:
            # press 'l' to show less region proposals
            num_show_rects -= increment
        elif k == 113:
            # press 'q' to quit
            break

    # close image show window
    cv2.destroyAllWindows()

        

    

