# Notes

This is a typical union-find problem. We connect nodes with black edges, and count how many groups there are in the end.

A group of N nodes will provide N-1 black edges. We sum up all groups and thus get the number of black edges in total.

Then we calculate the minimal cost by adding the cost of these black edges and the rest red edges.