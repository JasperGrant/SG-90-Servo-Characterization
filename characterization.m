
% Script to process inertial response of an SG-90 servo motor and find it's
% transfer function.
% Written by Jasper Grant April 3rd 2023

% Clear all data
clc; clear;

% Import servo data file
input = load('log.txt');

% Time is first column of file
t = input(:,1);
% Angle is second column of file
angle = input(:,2);
% Velocity is third column of file
vel = input(:,3);
% Output angle is receieved by integrating velocity
angle_output = 0.1*cumsum(vel);

% Plot angle vs time and integral of velocity vs time
plot(t, angle, t, angle_output);

% Format graph to look nice
title("Theoretical vs Real World response to different step inputs")
legend(["Theoretical" "Real World"])
xlabel("Time (ms)")
ylabel("Angle (Degrees)")

% Put into variable for system identification toolbox
data = iddata(angle_output, angle, 0.01);

% Split data into 26 distinct experiments
% Bounds of data cut off:
% Initial negative values as we are not interested in what was left from
% last experiment.
% Drop to 0 after step function as the intention is to plot the system with
% a step response.
multiExperimentData = data(1:300);
for i=300:300:7500
    sample = data(25+i:250+i);
    multiExperimentData = merge(sample, multiExperimentData);
end

% Plot for all 26 experiments
figure(2);
plot(multiExperimentData)

% Based on the assumption that the transfer function follows the common
% form for a servo transfer function (2 poles, 0 zeroes)
% Estimated transfer function
tf1 = tf(248.2, [1, 22.53, 241.1]);

% Plot step response for this tf
figure(3)
step(tf1);
% Plot bode plot for this tf
figure(4)
margin(tf1);
% Plot nyquist plot for this tf
figure(5);
nyquist(tf1);
