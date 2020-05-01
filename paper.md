---
title: 'CEST: A Centroid Extractor for Star Trackers'
tags:
  - C/C++
  - VHDL
  - Image Processing
  - Satellites
  - Star Trackers
authors:
  - name: Gabriel Mariano Marcelino
    orcid: 0000-0003-4889-6021
    affiliation: "1"
  - name: Victor Hugo Schulz
    orcid: 0000-0003-4889-6021
    affiliation: "2"
  - Laio Oriel Seman
    orcid: 0000-0003-4889-6021
    affiliation: "3"
  - Eduardo Augusto Bezerra
    orcid: 0000-0003-4889-6021
    affiliation: "1"
affiliations:
 - name: Space Technology Research Laboratory (SpaceLab), Universidade Federal de Santa Catarina
   index: 1
 - name: Laboratory of Spacecraft Environment Interaction Engineering (LaSEINE), Kyushu Institute of Technology
   index: 2
 - name: Applied Computer Science Master Program, Itajaí Valley University (UNIVALI)
   index: 3
date: 19 April 2020
bibliography: paper.bib
---

# Summary

`[@marcelino2020]`

# Introduction

The number of nanosatellites and picosatellites being launched have increased over the years. Associated with this growth, these smaller satellites have incrementally being able to replace functions previously only performed by bigger satellites, by the means of miniaturisation of their components. The reduced physical volume also implies in smaller solar panels and batteries being employed, resulting in stricter energy constraints for the satellite subsystems. These constraints have brought a demand for technology development toward optimising size, mass and energy consumption of CubeSat components.

At the beginning of space exploration, due to limitations in the available technologies, positioning and navigation systems were little efficient. For example, the first star trackers used to have film cameras through an almost entirely analog process \cite{zhang2017}. With the advance of electronics and the exponential growth of embedded devices processing capacity, the use of these types of sensors and system has becoming each time more accessible.

The use of star trackers began to be more widespread with the emergence of the first public star catalogs in the 1990s, such as, for example, the Hipparcos \cite{hipparcos-catalog}. Despite the advent of the CubeSat standard in 1999 \cite{cds}, the use of such sensors in small-sized satellites only started to be explored by the end of the 2000s, possibly due to the technological limitations (required physical size and power consumption) and lack of commercial solutions \cite{mcbryde-thesis}.

In this context, CEST (Centroid Extractor for Star Trackers) is an algorithm for identifying and determining the stars centroid in an image without storing the entire captured image and without the need for external memories or buffer.

# Centroid Determination

Considering that the input signal has a Gaussian behavior (pixels of stars), we propose the use of an IIR (infinite impulse response) filter to estimate the central coordinates of the centroids. For this purpose, it is possible to use a first-order filter (applied separately on each axis of the image) and with a gain that is constant and smaller than one, as presented in the following equations:

\begin{subequations}
    \begin{align}
        & X_{n} = [x_{n}, y_{n}] \\
        & G_{n} = a^{n} \\
        & Y_{n} = G_{n} \cdot X_{n} + (1 - G_{n}) \cdot Y_{n-1}
    \end{align}
\end{subequations}

with:

\begin{equation}
    \left\{ \begin{array}{l}
        Y_{0} = X_{0} \\
        a = 0.8 \\
    \end{array}\right.
\end{equation}

where:

* $x$ is a pixel position in the x-axis;
* $y$ is a pixel position in the y-axis;
* $X$ is the measured value (x and y-axis coordinates);
* $G_{n}$ is the weight of the current pixel;
* $a$ is an optimal constant to minimize the centroid position error;
* $Y_{n}$ is the estimation in the current iteration;
* $Y_{n−1}$ is the estimation of the previous iteration.

To illustrate this process, we have matrix (??), which represents a hypothetical image with a single star. Upon applying the previous equations to this matrix, after it goes through the threshold filter with a threshold equal to 150, we arrive at the results of ??. In this example, the system origin is the upper left corner, and the reading direction is from left to right, and from top to bottom.

\begin{figure}[!htb]
    \minipage{0.48\textwidth}
        \includegraphics[width=\linewidth]{doc/stars-image.png}
    \endminipage\hfill
    \minipage{0.48\textwidth}
        \includegraphics[width=\linewidth]{doc/stars-image-centroids.png}
    \endminipage\hfill
    \caption{Detected centroids in an image (left: sky image, right: detected centroids).}
\end{figure}

The proposed algorithm is also demonstrated in Figure (xx).

\begin{figure}[!htb]
    \begin{center}
        \subfigure[Pixel sliding window (red square).\label{fig:alg-demo-step-1}]{\includegraphics[width=0.2\textwidth]{figures/alg-ex-step-1}}
        \subfigure[First pixel to pass in the threshold filter. Distance threshold region (dashed circle).\label{fig:alg-demo-step-2}]{\includegraphics[width=0.2\textwidth]{figures/alg-ex-step-2}}
        \subfigure[Second pixel of the star.\label{fig:alg-demo-step-3}]{\includegraphics[width=0.2\textwidth]{figures/alg-ex-step-3}}
        \subfigure[Third pixel of the star.\label{fig:alg-demo-step-4}]{\includegraphics[width=0.2\textwidth]{figures/alg-ex-step-4}}
        \subfigure[Fourth pixel of the star.\label{fig:alg-demo-step-5}]{\includegraphics[width=0.2\textwidth]{figures/alg-ex-step-5}}
        \subfigure[Final result with the estimated centroid (green circle).\label{fig:alg-demo-step-6}]{\includegraphics[width=0.2\textwidth]{figures/alg-ex-step-6}}
        \caption{Proposed algorithm demonstration. Pixels coordinates (black dots). Star pixels with brightness variation at the borders (grey and white squares). Real centroid of the star (green cross). Estimated centroid (green circle).}
        \label{fig:algorithm-demo}
    \end{center}
\end{figure}

# Conclusion

# References
