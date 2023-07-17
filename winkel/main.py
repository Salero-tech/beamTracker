from fix import MovingHead, Mesurepoints
import math

distanceX = 1
distanceY = 9
height = 16

if (distanceX + distanceY < 10):
    exit("invalid input")

#distance form the backwall
winkelWand = math.acos((Mesurepoints.distance**2 + distanceY**2 - distanceX**2)/(2 * Mesurepoints.distance * distanceY**2))
walldistance = distanceY * math.sin(winkelWand)

#pan
distanceHeadPersonX = MovingHead.fromFront - walldistance
distanceHeadPersonY = math.sqrt(distanceY**2 - walldistance**2) - MovingHead.fromRight
distanceObove = math.sqrt(distanceHeadPersonX**2 + distanceHeadPersonY**2)

winkekelPan = math.asin(math.sin(90) / distanceObove * distanceHeadPersonX)
print(f"pan winkel: {math.degrees(winkekelPan)}")

#tilt
distanceHeadPersonH = MovingHead.height - height
distanceSide = math.sqrt(distanceHeadPersonX**2 + distanceHeadPersonH**2)

winkelTilt = math.asin(math.sin(90) / distanceSide * distanceHeadPersonX)
print(f"tilt winkel: {math.degrees(winkelTilt)}")