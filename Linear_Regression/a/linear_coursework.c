#include <stdio.h>
#include <math.h>

/******************************************************************************
 * This program takes an initial estimate of m and c and finds the associated 
 * rms error. It is then as a base to generate and evaluate 8 new estimates, 
 * which are steps in different directions in m-c space. The best estimate is 
 * then used as the base for another iteration of "generate and evaluate". This 
 * continues until none of the new estimates are better than the base. This is
 * a gradient search for a minimum in mc-space.
 * 
 * To compile:
 *   cc -o linear_coursework linear_coursework.c -lm
 * 
 * To run:
 *   ./linear_coursework
 * 
 * Dr Kevan Buckley, University of Wolverhampton, 2018
 *****************************************************************************/

typedef struct point_t {
  double x;
  double y;
}

 point_t;

int n_data = 1000;
point_t data[];

void print_data() {
  int i;
  for(i=0; i<n_data; i++) {
    printf("%0.2lf,%0.2lf\n", data[i].x, data[i].y);
  }
}

int main() {
  print_data();
  return 0;
}

point_t data[] = {
  {82.62,143.64},{79.22,139.25},{66.72,114.02},{69.96,107.30},
  {82.37,150.97},{84.31,145.76},{74.60,131.48},{65.14,92.59},
  {67.49,117.45},{75.99,152.75},{83.65,124.33},{79.57,133.40},
  {78.59,125.28},{62.81,113.43},{ 7.89,53.00},{86.86,147.37},
  {67.92,117.52},{79.28,134.60},{12.91,46.28},{34.20,88.17},
  {89.26,139.84},{81.34,108.48},{17.61,45.58},{25.89,84.81},
  {17.46,64.87},{36.78,87.69},{43.07,85.02},{88.31,155.88},
  { 7.94,32.81},{71.52,126.79},{96.48,152.64},{37.71,63.86},
  {59.17,111.02},{ 6.23,38.51},{56.98,103.93},{42.31,85.99},
  {38.96,86.16},{80.03,147.96},{61.84,108.22},{ 9.41,53.70},
  {31.15,69.52},{33.63,82.36},{ 8.99,36.54},{85.16,140.56},
  {60.80,107.85},{74.14,126.56},{68.19,116.90},{96.12,150.52},
  {39.41,74.92},{52.85,107.18},{87.84,139.87},{36.68,73.25},
  {12.14,53.99},{52.88,88.52},{88.90,144.05},{49.97,83.79},
  {65.76,112.58},{95.03,141.06},{91.48,141.08},{66.22,109.10},
  {38.52,84.02},{39.42,90.14},{75.87,129.78},{56.32,120.91},
  {56.46,82.45},{28.32,64.30},{85.11,139.84},{14.49,46.15},
  {78.10,121.23},{67.53,118.35},{44.94,96.09},{43.86,89.66},
  {77.05,127.88},{72.47,112.80},{59.23,100.53},{29.19,74.79},
  { 1.76,37.63},{75.49,133.61},{44.37,78.83},{51.56,99.61},
  {26.86,69.66},{53.36,105.72},{78.06,138.60},{90.40,145.24},
  {55.12,102.16},{44.12,85.53},{ 1.61,66.22},{38.33,85.13},
  {48.45,85.43},{84.17,125.62},{97.79,156.46},{75.40,138.06},
  {38.65,64.63},{68.76,118.86},{49.46,90.23},{38.58,69.65},
  {51.33,108.35},{68.45,100.35},{20.10,49.68},{20.35,55.70},
  {22.99,57.58},{20.02,57.85},{ 1.52,39.54},{88.03,123.91},
  {12.28,55.13},{40.42,87.22},{79.46,137.74},{55.51,109.59},
  {42.32,95.33},{40.05,95.57},{81.95,138.75},{15.25,65.87},
  {51.77,97.90},{84.95,129.37},{12.24,38.13},{35.70,76.69},
  {55.44,104.90},{57.01,104.25},{14.29,32.84},{57.64,97.02},
  {34.63,80.72},{56.26,88.01},{17.07,56.99},{ 0.69,42.05},
  { 9.30,44.85},{99.33,145.84},{15.44,63.21},{15.86,64.74},
  {32.66,76.76},{74.56,124.44},{93.84,161.59},{95.59,134.80},
  { 8.50,34.15},{19.82,67.98},{ 8.31,42.30},{81.70,146.41},
  {99.98,177.42},{27.18,46.08},{17.10,58.83},{18.69,54.44},
  {95.47,155.57},{20.65,63.61},{ 8.46,35.22},{50.36,88.65},
  {31.84,64.26},{64.36,120.60},{63.53,135.85},{80.80,121.53},
  {44.95,76.11},{71.81,120.17},{ 5.25,42.18},{22.78,66.52},
  {62.79,102.70},{ 6.19,23.68},{22.43,50.04},{63.23,102.92},
  {60.63,109.83},{55.04,111.93},{22.71,59.24},{40.92,101.14},
  {82.09,152.68},{73.78,123.53},{59.62,107.77},{51.43,92.01},
  {61.98,103.02},{41.63,93.06},{79.66,133.29},{26.77,56.64},
  {25.52,64.31},{18.42,63.25},{23.79,53.36},{21.40,67.88},
  {13.56,68.51},{61.86,112.93},{49.51,102.35},{99.65,154.30},
  { 2.01,55.26},{76.61,138.97},{32.28,78.91},{94.59,140.12},
  {72.44,119.48},{62.56,126.79},{23.09,60.32},{60.49,122.35},
  {55.73,111.55},{56.00,90.30},{57.82,110.86},{72.16,129.86},
  {56.21,101.96},{46.61,91.92},{39.62,98.36},{55.46,90.61},
  {63.88,112.16},{14.87,66.18},{18.72,56.15},{67.86,123.97},
  {50.63,87.35},{18.99,78.13},{30.81,81.15},{27.11,66.33},
  { 1.29,34.57},{26.17,74.76},{43.55,87.46},{33.13,67.28},
  {64.03,115.40},{23.25,59.72},{36.65,73.93},{67.03,113.55},
  {19.27,54.33},{ 0.88,32.90},{60.18,112.94},{45.55,92.52},
  {35.73,89.14},{70.56,144.28},{28.16,59.88},{53.80,90.55},
  {67.83,122.73},{21.25,65.94},{92.82,149.51},{62.34,102.77},
  {19.75,62.76},{20.42,58.69},{97.11,155.59},{66.81,106.37},
  {21.28,85.17},{79.48,129.43},{48.87,100.18},{99.08,159.84},
  {42.91,87.40},{89.36,130.57},{29.49,79.75},{87.19,157.59},
  {37.55,88.86},{94.27,162.89},{19.47,69.66},{10.18,34.90},
  {73.45,115.57},{95.31,146.76},{75.44,130.83},{36.60,78.12},
  {69.72,123.84},{43.48,83.63},{25.29,62.44},{40.81,84.96},
  {61.28,100.00},{90.23,122.50},{41.17,82.53},{39.17,80.20},
  {38.03,85.86},{47.24,107.77},{78.51,126.37},{71.35,136.35},
  {20.18,58.39},{43.88,98.72},{39.82,90.17},{65.81,107.70},
  {81.60,137.91},{32.91,77.79},{71.08,134.21},{ 6.55,32.97},
  {97.98,182.46},{97.55,146.96},{47.57,83.70},{25.50,57.85},
  {16.48,68.61},{12.93,49.56},{19.77,64.09},{11.50,57.18},
  {24.28,61.37},{98.06,159.65},{35.39,83.78},{72.10,123.94},
  {47.15,88.18},{79.12,125.02},{86.72,128.30},{25.50,59.34},
  {38.70,84.31},{44.59,72.21},{69.68,115.42},{98.29,161.40},
  {49.91,99.31},{59.00,99.58},{99.63,165.00},{86.43,131.46},
  { 8.40,73.55},{38.33,86.13},{20.04,76.60},{88.20,147.50},
  {73.14,124.18},{98.98,147.89},{29.12,84.86},{66.70,136.38},
  {85.95,143.52},{28.86,83.57},{39.10,83.34},{42.88,89.76},
  {99.16,135.63},{17.61,32.98},{50.98,81.26},{18.62,77.96},
  {82.57,135.99},{ 6.99,32.51},{68.31,95.84},{80.18,121.30},
  {86.61,132.27},{35.23,77.59},{26.40,77.84},{70.73,114.49},
  {22.33,75.18},{44.41,79.23},{88.60,144.22},{ 5.74,31.99},
  {46.12,87.70},{22.97,60.73},{88.35,143.46},{19.27,51.67},
  { 0.43,30.75},{26.75,65.77},{56.82,98.89},{ 5.10,36.02},
  {54.78,97.82},{11.13,54.78},{ 7.25,39.69},{70.84,119.90},
  {20.44,52.04},{73.13,132.93},{67.74,129.64},{64.12,111.38},
  {56.36,104.76},{72.38,142.42},{19.22,46.24},{69.70,138.62},
  {65.11,130.46},{10.15,42.51},{62.91,111.00},{76.91,138.35},
  {31.73,82.63},{74.72,141.07},{23.81,80.26},{49.44,109.01},
  {89.40,145.36},{75.64,126.23},{95.05,160.70},{ 9.14,44.44},
  { 3.14,56.02},{13.13,60.31},{ 5.66,45.78},{58.44,101.70},
  {18.44,64.06},{79.74,110.80},{74.69,143.13},{86.76,140.94},
  {92.72,147.92},{36.02,68.24},{43.86,100.72},{67.29,124.46},
  {25.27,74.03},{26.89,89.76},{64.74,102.37},{55.55,101.28},
  {54.57,94.76},{90.82,159.06},{50.94,88.58},{85.23,143.80},
  {84.10,134.25},{50.32,80.07},{26.18,74.39},{20.14,61.60},
  {73.84,116.93},{12.47,52.02},{94.53,160.73},{69.73,132.66},
  {57.01,110.57},{23.09,79.75},{ 7.51,53.37},{66.44,121.20},
  {59.85,122.48},{10.61,39.08},{30.43,80.72},{97.78,134.77},
  {94.80,137.26},{88.87,153.41},{69.18,125.45},{57.83,96.24},
  {99.52,142.09},{20.07,58.81},{43.33,87.39},{33.39,84.28},
  {54.63,105.99},{10.66,45.57},{51.08,92.23},{72.80,137.24},
  {77.45,123.15},{21.22,61.90},{19.05,65.00},{92.67,145.11},
  {12.58,25.93},{25.04,76.61},{72.01,123.15},{82.66,140.16},
  {50.64,99.43},{29.69,71.31},{35.48,83.40},{96.65,135.26},
  { 0.64,45.73},{30.21,69.71},{49.47,98.38},{30.36,74.15},
  {94.04,143.34},{ 6.48,41.88},{77.61,126.35},{93.61,148.24},
  {28.74,75.81},{89.71,138.74},{89.00,136.11},{29.19,68.02},
  {54.98,77.61},{16.65,52.39},{37.61,89.53},{70.59,140.90},
  {89.11,149.45},{43.82,87.12},{60.80,100.38},{39.79,78.06},
  {36.67,69.27},{22.22,61.16},{94.05,167.69},{47.03,98.64},
  {12.89,64.97},{74.02,120.44},{44.05,93.70},{22.61,72.47},
  {15.58,61.56},{23.98,66.59},{36.55,80.64},{13.48,41.83},
  { 3.51,28.11},{54.23,115.43},{72.25,141.21},{ 6.54,46.54},
  {50.91,91.17},{23.54,58.78},{76.58,118.57},{52.98,79.68},
  {65.59,113.50},{76.97,136.60},{37.66,84.94},{ 9.64,43.57},
  {44.47,78.52},{80.70,128.38},{35.23,79.08},{74.83,135.33},
  { 7.24,45.29},{ 2.08,38.64},{99.99,153.14},{93.64,153.68},
  {78.66,135.42},{57.50,85.69},{ 9.87,64.84},{86.65,139.58},
  {45.13,111.22},{45.16,95.45},{66.66,114.59},{52.62,85.21},
  {59.74,106.15},{59.38,96.52},{95.55,141.02},{25.16,63.67},
  {77.50,122.90},{42.63,108.45},{73.15,113.25},{15.09,46.81},
  {27.31,67.28},{ 6.43,55.44},{91.90,128.60},{33.15,82.79},
  {92.46,145.60},{59.03,124.09},{60.89,122.58},{ 9.06,50.68},
  {70.93,121.48},{83.57,151.17},{ 0.32,19.12},{96.68,156.19},
  {61.67,103.26},{84.04,137.79},{52.28,98.88},{27.15,69.06},
  {43.23,95.21},{66.89,120.50},{15.00,56.44},{63.75,120.23},
  {43.10,81.14},{ 3.38,36.18},{41.75,93.54},{82.97,156.76},
  {20.06,60.75},{90.00,140.19},{49.14,98.77},{ 8.71,45.99},
  {21.88,60.57},{ 4.24,52.96},{78.83,143.05},{35.15,73.25},
  {42.55,70.43},{38.64,85.49},{15.27,77.22},{81.54,125.19},
  {40.08,72.54},{34.36,90.58},{93.40,162.74},{87.43,147.54},
  {79.07,130.11},{92.35,124.86},{43.08,89.66},{65.19,111.27},
  {42.87,88.02},{63.67,100.97},{82.92,116.86},{38.80,98.12},
  {49.62,89.76},{48.53,120.93},{19.89,59.94},{14.33,39.33},
  {92.42,144.83},{73.82,147.55},{ 4.30,24.13},{ 8.74,55.38},
  {99.08,128.37},{14.74,40.75},{64.42,97.61},{10.02,56.84},
  {51.40,100.29},{49.59,101.50},{66.66,119.86},{17.70,54.65},
  {54.38,91.50},{57.88,108.13},{60.26,97.92},{23.92,54.29},
  {77.19,141.90},{98.36,159.01},{53.05,93.55},{28.00,61.90},
  {40.03,84.80},{69.36,115.61},{76.80,129.05},{68.89,132.79},
  {70.77,126.39},{45.62,86.67},{28.43,66.88},{58.14,113.24},
  { 0.99,27.33},{14.50,24.61},{62.10,130.65},{ 5.25,42.89},
  {56.06,110.85},{81.79,123.81},{53.62,87.89},{31.98,87.89},
  {73.20,126.45},{ 6.35,46.62},{50.25,103.54},{11.15,60.98},
  {68.49,121.77},{47.64,93.29},{22.19,82.28},{83.54,127.48},
  {22.92,69.32},{55.08,124.22},{49.94,90.74},{54.35,101.26},
  {59.01,104.14},{84.76,144.30},{42.21,96.36},{68.34,115.77},
  {98.38,157.44},{18.72,67.82},{ 6.26,33.62},{32.68,91.66},
  {81.58,131.25},{45.92,87.55},{85.41,143.82},{ 1.17,34.39},
  {35.13,70.17},{55.80,96.77},{19.49,57.39},{60.48,117.40},
  {53.27,101.00},{63.11,125.56},{31.27,62.46},{77.41,144.68},
  {54.81,94.20},{56.79,97.41},{ 8.75,33.66},{83.69,145.09},
  {80.06,112.13},{95.00,153.86},{74.80,111.46},{38.49,90.82},
  {75.55,123.14},{ 4.33,49.85},{93.50,146.71},{98.43,156.61},
  {99.39,167.88},{98.34,155.22},{85.33,140.93},{72.75,132.34},
  {27.73,71.66},{60.35,105.85},{34.91,72.25},{30.39,72.85},
  {47.50,85.93},{98.35,156.85},{86.15,140.07},{75.54,127.50},
  { 8.44,25.38},{59.08,119.44},{42.80,99.01},{ 4.87,60.72},
  {13.44,58.92},{75.81,130.55},{52.72,120.67},{45.12,100.97},
  {18.35,57.66},{67.54,112.55},{52.88,96.63},{60.76,106.83},
  { 7.71,48.25},{63.21,116.04},{98.09,165.80},{21.66,53.23},
  {16.55,62.28},{49.08,105.83},{91.74,130.45},{50.33,97.30},
  {58.01,96.82},{ 2.37,41.00},{11.82,42.25},{67.64,121.12},
  { 7.25,41.94},{86.21,167.41},{84.99,149.99},{78.24,129.61},
  {91.79,146.83},{21.16,64.52},{52.51,90.71},{11.45,50.45},
  { 8.03,49.21},{31.69,76.57},{84.07,140.74},{58.84,116.72},
  {14.32,60.98},{13.72,63.44},{64.01,111.97},{83.49,134.00},
  {61.03,106.95},{84.20,158.65},{59.54,100.32},{42.72,86.38},
  {62.12,110.49},{34.78,79.02},{51.68,94.00},{52.90,121.83},
  {91.48,157.53},{16.53,66.79},{34.80,62.46},{76.03,127.74},
  {96.00,157.51},{55.30,118.82},{ 7.53,56.38},{89.11,153.52},
  {64.06,113.47},{72.78,128.42},{52.33,106.65},{35.49,58.08},
  {23.86,47.85},{ 0.51,34.96},{ 0.87,47.44},{26.22,79.20},
  {59.48,92.73},{94.30,145.72},{99.17,147.06},{95.65,150.17},
  { 2.97,57.99},{44.15,96.40},{74.09,113.47},{38.18,90.33},
  { 2.60,40.37},{74.15,123.58},{46.94,89.69},{56.80,116.49},
  {13.28,41.38},{26.68,65.65},{ 3.79,47.29},{19.60,57.11},
  {77.14,117.29},{33.66,82.26},{37.43,78.54},{44.87,80.70},
  {41.85,96.73},{52.91,99.78},{27.26,58.56},{82.36,136.35},
  {67.14,110.96},{75.64,150.52},{41.84,85.17},{42.53,88.68},
  {73.13,124.14},{43.92,83.71},{89.08,129.77},{15.17,50.48},
  {27.77,71.26},{50.83,94.32},{13.70,49.60},{62.45,122.38},
  {72.11,125.96},{83.70,140.91},{ 3.01,34.32},{49.59,100.91},
  {64.37,126.61},{12.40,30.14},{75.79,123.14},{18.63,52.71},
  {48.36,86.60},{77.95,131.41},{83.02,135.54},{79.84,132.62},
  {67.01,135.84},{30.76,59.95},{37.23,77.44},{76.31,134.93},
  {36.48,81.52},{96.24,138.02},{90.64,145.85},{49.16,94.09},
  {13.20,49.03},{61.54,112.65},{79.97,116.61},{30.95,87.91},
  {22.32,62.53},{78.90,145.23},{96.02,161.48},{73.26,128.71},
  {76.29,126.79},{ 9.79,56.28},{47.84,101.86},{38.05,76.28},
  { 5.99,29.29},{50.15,87.87},{94.78,153.60},{97.51,138.09},
  {17.62,56.40},{ 4.59,52.08},{74.95,115.90},{89.73,150.76},
  {34.18,84.98},{37.29,75.88},{63.82,105.85},{44.03,80.35},
  { 5.31,44.13},{24.05,74.51},{88.10,152.76},{32.02,60.73},
  {40.76,90.83},{43.14,86.01},{12.88,47.21},{45.02,90.29},
  {69.05,123.82},{ 5.18,43.45},{69.09,121.16},{ 1.70,59.63},
  {96.83,153.69},{42.45,88.92},{82.68,138.04},{91.18,142.38},
  {45.27,101.37},{96.31,150.99},{94.75,146.67},{ 7.82,42.96},
  {10.33,59.20},{75.16,122.72},{20.65,43.76},{98.92,163.71},
  {74.42,129.19},{76.03,105.92},{27.46,61.01},{98.10,147.14},
  {86.83,144.03},{92.89,143.68},{26.59,65.66},{90.10,134.67},
  {32.33,64.44},{74.73,125.56},{45.76,96.84},{62.15,110.06},
  {27.64,72.59},{79.84,137.94},{45.96,102.33},{14.87,68.63},
  {64.84,94.17},{97.18,159.74},{12.76,70.40},{75.87,119.52},
  {65.32,114.29},{ 1.96,38.65},{11.32,47.31},{91.92,147.15},
  {29.28,60.02},{63.07,124.64},{57.13,106.49},{51.57,94.05},
  {81.76,130.32},{98.68,151.76},{20.62,57.07},{95.58,158.24},
  {97.66,161.62},{95.87,154.26},{12.54,57.52},{80.81,139.82},
  {24.09,85.28},{61.35,117.04},{ 6.38,37.89},{52.79,112.56},
  {51.81,115.40},{76.00,125.47},{73.94,113.21},{52.47,118.65},
  {46.82,105.37},{ 2.57,48.87},{36.53,86.79},{33.51,87.79},
  {46.47,107.76},{35.00,79.25},{32.42,66.19},{38.53,79.02},
  {81.54,153.90},{33.03,70.32},{85.87,154.72},{25.05,68.21},
  {52.62,100.96},{71.52,113.86},{96.50,162.79},{61.19,119.20},
  {75.06,124.88},{91.21,172.56},{ 1.06,45.95},{43.00,89.85},
  {87.44,145.76},{70.01,115.13},{52.63,107.09},{18.96,59.65},
  {61.16,117.38},{ 9.90,40.46},{74.28,131.56},{25.61,74.46},
  {44.43,85.04},{73.34,126.59},{65.19,120.62},{42.56,87.15},
  {33.56,61.94},{94.26,154.62},{40.97,105.30},{55.82,105.39},
  {54.03,105.87},{77.96,112.57},{61.54,115.34},{53.30,97.18},
  {61.03,118.21},{59.72,118.40},{42.32,81.21},{43.97,101.70},
  {63.65,111.32},{48.04,89.01},{29.71,79.07},{64.66,111.77},
  { 5.20,36.90},{44.69,70.70},{48.39,93.12},{39.11,85.49},
  { 7.87,39.97},{36.74,65.34},{40.58,78.87},{68.52,107.86},
  {13.36,70.70},{34.05,88.29},{44.86,84.46},{98.74,155.65},
  {57.23,91.08},{96.78,159.49},{97.24,154.92},{52.10,107.55},
  {79.40,140.27},{48.37,92.94},{42.86,76.57},{80.40,129.20},
  {71.79,119.60},{25.95,64.59},{67.29,107.62},{65.14,101.76},
  {67.88,103.52},{94.29,148.22},{20.35,64.79},{38.07,84.71},
  {19.04,72.31},{70.61,124.28},{56.30,112.31},{47.85,83.62},
  {63.75,113.88},{49.42,107.12},{41.37,108.22},{49.45,103.25},
  {31.54,73.41},{20.45,73.47},{77.60,140.47},{35.53,66.36},
  {35.01,71.18},{23.54,87.88},{86.11,140.79},{27.29,66.52},
  {96.41,156.23},{ 1.22,40.10},{56.71,95.69},{49.34,89.56},
  {86.82,157.76},{10.33,53.35},{28.97,66.60},{69.44,115.16},
  {91.99,140.88},{25.22,68.64},{80.47,142.28},{50.94,106.95},
  {15.01,67.22},{82.84,130.17},{ 7.09,39.07},{28.05,61.00},
  {34.38,95.58},{56.82,111.43},{91.54,153.01},{33.59,58.11},
  {86.34,126.85},{73.22,119.85},{57.55,106.39},{45.41,107.05},
  {65.45,130.24},{10.82,34.30},{18.94,76.34},{49.46,97.76},
  { 6.02,49.50},{90.01,157.13},{98.28,150.28},{72.03,136.60},
  {52.95,90.61},{22.18,64.86},{83.00,136.75},{49.82,100.75},
  { 4.83,38.59},{28.17,66.05},{74.69,136.76},{62.98,131.26},
  {74.15,102.46},{38.90,75.39},{28.53,51.70},{64.98,132.94},
  {25.26,78.46},{43.28,90.84},{49.41,88.50},{22.44,63.14},
  {59.23,94.06},{10.50,53.43},{ 3.32,28.93},{66.88,120.02},
  {34.44,89.78},{82.72,138.68},{31.66,74.13},{76.27,117.85},
  {20.74,73.55},{74.74,128.33},{35.99,71.58},{84.89,152.21},
  {23.94,83.53},{30.66,56.45},{65.25,125.27},{34.95,80.86},
  {65.64,110.03},{47.43,100.50},{11.13,35.41},{96.77,164.03},
  {45.42,105.73},{77.64,152.56},{87.27,141.47},{86.36,129.86},
  {42.91,82.47},{ 3.59,51.65},{64.66,106.56},{66.07,103.90},
  {65.71,111.83},{34.29,95.12},{26.94,46.77},{99.28,144.57}
};
