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

# Conclusion

# References
