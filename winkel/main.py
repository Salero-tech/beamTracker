from fix import MovingHead, Mesurepoints
import math

distanceX = 5
distanceY = 5
height = 15

if (distanceX + distanceY < Mesurepoints.distance):
    exit("invalid input")

#distance form the backwall
winkelWand = math.acos((Mesurepoints.distance**2 + distanceY**2 - distanceX**2)/(2 * Mesurepoints.distance * distanceY))
walldistance = distanceY * math.sin(winkelWand)

#pan
distanceHeadPersonX = MovingHead.fromFront - walldistance
distanceHeadPersonY = math.sqrt(distanceY**2 - walldistance**2) - MovingHead.fromLeft
distanceObove = math.sqrt(distanceHeadPersonX**2 + distanceHeadPersonY**2)

winkekelPan = math.asin(math.sin(math.radians(90)) / distanceObove * distanceHeadPersonX)
print(f"pan winkel: {math.degrees(winkekelPan)}")

#tilt
distanceHeadPersonH = MovingHead.height - height
distanceSide = math.sqrt(distanceHeadPersonX**2 + distanceHeadPersonH**2)

winkelTilt = math.asin(math.sin(math.radians(90)) / distanceSide * distanceHeadPersonX)
print(f"tilt winkel: {math.degrees(winkelTilt)}")