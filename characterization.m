clc; clear;

input = load('log.txt');

t = input(:,1);
angle = input(:,2);
vel = input(:,3);

plot(t, angle, t,0.1*cumsum(vel));