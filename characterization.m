clc; clear;

input = load('log.txt');

t = input(:,1);
angle = input(:,2);
vel = input(:,3);

plot(t, angle, t,0.1*cumsum(vel));
title("Theoretical vs Real World response to different step inputs")
legend(["Theoretical" "Real World"])
xlabel("Time (ms)")
ylabel("Angle (Degrees)")