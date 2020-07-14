import serial
import time
import cv2
import numpy as np
import os
import glob

 
def nothing(x):
    pass
 
cap = cv2.VideoCapture(1)
cap2= cv2.VideoCapture(2)
angle90 = 90
scale = 1.0
arduino = serial.Serial('COM10',57600)
time.sleep(1)
print ("",arduino.readline().decode())

while True:
    _, frame = cap.read()
    __,frame2 = cap2.read()

    img = cv2.resize(frame,(500,500))
    img1 = cv2.resize(frame2,(500,500))
    (h, w) = img.shape[:2]
   # calculate the center of the image
    center = (w / 2, h / 2)
    # 90 degrees
    M = cv2.getRotationMatrix2D(center, angle90, scale)
    frame = cv2.warpAffine(img, M, (h, w))
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
 
    lower_blue = np.array([100,20,130])
    upper_blue = np.array([130,255,255])
    mask = cv2.inRange(hsv, lower_blue, upper_blue)
    result = cv2.bitwise_and(frame,frame, mask=mask)
    
    img=cv2.cvtColor(result, cv2.COLOR_BGR2GRAY)
    ret, mask_ = cv2.threshold(img, 0, 255, cv2.THRESH_BINARY)
    mask_inv = cv2.bitwise_not(mask_)
 
    road = cv2.bitwise_and(frame,frame,mask=mask_)
    car = cv2.bitwise_and(img1, img1, mask=mask_inv)
    result= cv2.add(road, car)
    ball = result[120:300,50:400]
                  
    hsv = cv2.cvtColor(ball, cv2.COLOR_BGR2HSV)

    lower_blue = np.array([80,84,130])
    upper_blue = np.array([130,255,255])

    mask = cv2.inRange(hsv, lower_blue, upper_blue)
    res = cv2.bitwise_and(ball, ball, mask=mask)

    cv2.imshow("img",ball)
    
    crop_img = ball[155:170, 110:260] # Convert BGR to HSV
    hsv = cv2.cvtColor(crop_img, cv2.COLOR_BGR2HSV)
    # define range of blue color in HSV
    lower_blue = np.array([80,84,138])
    upper_blue = np.array([130,255,255])
    # Threshold the HSV image to get only blue colors
    mask = cv2.inRange(hsv, lower_blue, upper_blue)
    # Bitwise-AND mask and original image
    res = cv2.bitwise_and(crop_img,crop_img, mask= mask)
    # Convert to grayscale
    gray = cv2.cvtColor(res, cv2.COLOR_BGR2GRAY)
    # Gaussian blur
    blur = cv2.GaussianBlur(gray,(5,5),0)
    # Color thresholding
    ret,thresh = cv2.threshold(blur,0,255,cv2.THRESH_BINARY)
    # Find the contours of the frame
    _, conto,hierarchy= cv2.findContours(thresh.copy(), 1, cv2.CHAIN_APPROX_NONE)
    # Find the biggest contour (if detected)

     #find road
    crop_img =frame2[200:300, 0:500]
    hsv_1 = cv2.cvtColor(crop_img, cv2.COLOR_BGR2HSV)
        # define range of blue color in HSV
    lower_road = np.array([0,0,100])
    upper_road = np.array([130,255,255])
        # Threshold the HSV image to get only blue colors
    mask_road = cv2.inRange(hsv_1, lower_road, upper_road)
        # Bitwise-AND mask and original image
    res_road= cv2.bitwise_and(frame2,frame2, mask= mask_road)
        # Convert to grayscale
    gray_road= cv2.cvtColor(res_road, cv2.COLOR_BGR2GRAY)
        # Gaussian blur
    blur_road = cv2.GaussianBlur(gray_road,(5,5),0)
        # Color thresholding
    ret_road,thresh_road = cv2.threshold(blur_road,0,255,cv2.THRESH_BINARY)
        # Find the contours of the frame
    road, conto_road,hierarchy_road= cv2.findContours(thresh_road.copy(), 1, cv2.CHAIN_APPROX_NONE)
        # Find the biggest contour (if detected)

    if len(conto) > 0:
        c = max(conto, key=cv2.contourArea)
        M = cv2.moments(c)
        cx = int(M['m10']/M['m00'])
        cy = int(M['m01']/M['m00'])
        cv2.line(crop_img,(cx,0),(cx,720),(255,0,0),1)
        cv2.line(crop_img,(0,cy),(1280,cy),(255,0,0),1)
        cv2.drawContours(crop_img, conto, -1, (0,255,0), 1)
        if cx >= 100:
            print ("Turn Right!")
            arduino.write('Right'.encode())
            print ("",arduino.readline().decode())
            
        if cx < 100 and cx > 50:
            print ("On Track!")
            arduino.write('Track'.encode())
            print ("",arduino.readline().decode())
            if len(conto_road) > 0:
                c = max(conto_road, key=cv2.contourArea)
                M = cv2.moments(c)
                cx = int(M['m10']/M['m00'])
                cy = int(M['m01']/M['m00'])
                cv2.line(frame2,(cx,0),(cx,720),(255,0,0),1)
                cv2.line(frame2,(0,cy),(1280,cy),(255,0,0),1)
                cv2.drawContours(frame2, conto, -1, (0,255,0), 1)
                if cx >= 150:
                    print ("Turn Right_road")
                    arduino.write('Right'.encode())
                    print ("",arduino.readline().decode())
                                    
                if cx < 150 and cx > 50:
                    print ("On Track_road")
                    arduino.write('Track'.encode())
                    print ("",arduino.readline().decode())
                               
                if cx <= 50:
                    print ("Turn Left_road")
                    arduino.write('Left'.encode())
                    print ("",arduino.readline().decode())
            
        if cx <= 50:
            print ("Turn Left")
            arduino.write('Left'.encode())
            print ("",arduino.readline().decode())
        
    else:
        print ("I don't see the line")
        arduino.write('I_dont_see_the_line'.encode())
        print ("",arduino.readline().decode())
        
    #Display the resulting frame
    cv2.imshow('frame',crop_img)
    cv2.imshow('frame1',res)
    cv2.imshow('road',frame2)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

 
cap.release()
cv2.destroyAllWindows()


