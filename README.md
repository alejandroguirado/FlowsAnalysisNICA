# Flows-Analysis-NICA
In relativistic heavy ion collisions the distribution in the overlap region of the colliding nuclei is affected by the pressure gradients created in the initial moment of collision, which can be characterized by the coefficients of Fourier expansion of azimuth distribution in momentum coordinates. In experimental particle physics, the capability to measure the event plane angle is very important. The event plane angle can be estimated via the azimuthal distributions of particles produced in the collision. This macros were made to measure this observables in simulations for NICA experiments. A brief description of the codes:

* EventPlaneAngleDifWeights-> Using differents weights for the event plane angle standard method.
* EventPlaneAnglePrimaryTracks-> Selecting all particles that are primary tracks.
* EventPlaneAngleResolution-> After the event plane angle is calculated is possible to compare it with the real plane angle(Monte Carlo).





## Brief theory overview



In non-central collisions the shape of the interaction region depends on
the impact parameter of the collision. If the impact parameter is zero, the shape of the interaction region is a sphere centered at the origin. But, if the impact parameter is not null, the interaction shape could be an ellipse creating an azimuthal transverse momentum distribution due the anisotropy of the reaction volume.  To characterize this phenomenon, it is used a Fourier expansion of the moment distribution with respect to the reaction plane. Experimentally this function can be constructed by data, regarding to periodicity of the function $r(\phi)$ is possible to write it in the form of Fourier expansion. 


<a href="https://www.codecogs.com/eqnedit.php?latex=E&space;\frac{d^{3}N}{d^{3}p}&space;=\frac{1}{2\pi}\frac{d^{2}N}{p_{T}dp_{T}&space;dy&space;}\left[&space;1&space;&plus;&space;2\sum_{n=1}^{\infty}v_{n}&space;(p_T,y)&space;cos[n(\phi-\Psi_{RP})&space;]&space;\right]&space;\label{distr}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?E&space;\frac{d^{3}N}{d^{3}p}&space;=\frac{1}{2\pi}\frac{d^{2}N}{p_{T}dp_{T}&space;dy&space;}\left[&space;1&space;&plus;&space;2\sum_{n=1}^{\infty}v_{n}&space;(p_T,y)&space;cos[n(\phi-\Psi_{RP})&space;]&space;\right]&space;\label{distr}" title="E \frac{d^{3}N}{d^{3}p} =\frac{1}{2\pi}\frac{d^{2}N}{p_{T}dp_{T} dy }\left[ 1 + 2\sum_{n=1}^{\infty}v_{n} (p_T,y) cos[n(\phi-\Psi_{RP}) ] \right] \label{distr}" /></a>

Solving for the event plane angle using Fourier analysis we get that the event plane angle can be calculated as:

<a href="https://www.codecogs.com/eqnedit.php?latex=\Psi_n&space;=&space;\frac{1}{n}&space;Tan^{-1}\left[&space;\frac{&space;\sum_{i}^{N}&space;w^{i}cos(n\phi_i)&space;}{&space;\sum_{i}^{N}&space;w^{i}&space;sin(n\phi_i)}&space;\right]&space;\label{eq:eventplaneangle}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\Psi_n&space;=&space;\frac{1}{n}&space;Tan^{-1}\left[&space;\frac{&space;\sum_{i}^{N}&space;w^{i}cos(n\phi_i)&space;}{&space;\sum_{i}^{N}&space;w^{i}&space;sin(n\phi_i)}&space;\right]&space;\label{eq:eventplaneangle}" title="\Psi_n = \frac{1}{n} Tan^{-1}\left[ \frac{ \sum_{i}^{N} w^{i}cos(n\phi_i) }{ \sum_{i}^{N} w^{i} sin(n\phi_i)} \right] \label{eq:eventplaneangle}" /></a>



Here the weights(w) in the last equations are commonly used as the transverse momentum. Here, in the codes the weights are the energy loss per cell and the multiplcity for BeBe detector of NICA collaboration. 
