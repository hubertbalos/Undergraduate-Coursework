# -*- coding: utf-8 -*-
"""
Created on Fri Nov 27 12:48:15 2020

@author: Huber
"""
import numpy as np
import matplotlib.pyplot as plt
import math
from scipy.optimize import curve_fit


planetname, detection = np.genfromtxt("Exoplanet_catalog_2019.csv", dtype=str, skip_header=1, delimiter=",", unpack = True, usecols=(0,5))
period, semimajor, starmass = np.genfromtxt("Exoplanet_catalog_2019.csv", usecols=(1,2,9), skip_header=1, delimiter=",", unpack = True)

nothing = []

x = -1
for item in period:
    x = x + 1
    if math.isnan(item) == True:
        nothing.append(x)

x = -1
for item in semimajor:
    x = x + 1
    if math.isnan(item) == True:
        nothing.append(x)

x = -1
for item in starmass:
    x = x + 1
    if math.isnan(item) == True:
        nothing.append(x)

period = np.delete(period, [nothing])
semimajor = np.delete(semimajor, [nothing])
starmass = np.delete(starmass, [nothing])
planetname = np.delete(planetname, [nothing])
detection = np.delete(detection, [nothing])
#-----------------------------------------------------------------------------

radialvelocity = []
primarytransit = []

x = -1
for item in detection:
    x = x + 1 
    if item == "Radial Velocity":
        radialvelocity.append(period[x])
    else:
        primarytransit.append(period[x])
    
nbins = np.linspace(0, 2500, 30)

plt.hist(radialvelocity, bins=nbins, alpha=0.5, label='radial velocity')
plt.hist(primarytransit, bins=nbins, alpha=0.5, label='primary transit')
plt.legend(loc='upper right')
plt.xlabel("Orbital period")
plt.ylabel("Number of planets")
plt.show()  
    #-----------------------------------------------------------------------------    

radialvelocity_2 = []
primarytransit_2 = []

x = -1
for item in detection:
    x = x + 1 
    if item == "Radial Velocity":
        radialvelocity_2.append(starmass[x])
    else:
        primarytransit_2.append(starmass[x])

nbins = np.linspace(0, 1, 11)

plt.hist(radialvelocity_2, bins=nbins, alpha=0.5, label='Radial velocity')
plt.hist(primarytransit_2, bins=nbins, alpha=0.5, label='Primary transit')
plt.legend(loc='upper right')
plt.xlabel("Star mass")
plt.ylabel("Number of planets")
plt.show()  
#-----------------------------------------------------------------------------

nbins = np.linspace(1, 5, 5)

plt.hist(radialvelocity_2, bins=nbins, alpha=0.5, label='Radial velocity')
plt.hist(primarytransit_2, bins=nbins, alpha=0.5, label='Primary transit')
plt.legend(loc='upper right')
plt.xlabel("Star mass")
plt.ylabel("Number of planets")
plt.show()  
#-----------------------------------------------------------------------------

badvalue = []

x = -1
for item in starmass:
    x = x + 1
    if item < 0.7:
        badvalue.append(x)
     
x = -1
for item in period:
    x = x + 1
    if item > 10000:
        badvalue.append(x)

new_period = np.delete(period, [badvalue])
new_starmass = np.delete(starmass, [badvalue])
new_semimajor = np.delete(semimajor, [badvalue])

plt.plot(new_semimajor ** 3 / new_starmass, new_period ** 2, "r.")
plt.xlabel("Semi major axis ^3 / Star mass (AU^3 / M☉) ( ")
plt.ylabel("Orbital period ^2 (Days^2)")
#-----------------------------------------------------------------------------

def str_line(x,a,b):
    return a * x + b

popt, pcov = curve_fit(str_line, new_semimajor ** 3 / new_starmass, new_period ** 2, sigma = None)

x_line = np.linspace(0, 600, 1000)

plt.plot(x_line, str_line(x_line, *popt), "k-")

