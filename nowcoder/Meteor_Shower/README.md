# Notes

Typical BFS.

A trap is that the search radius must go beyond 300. Meteors can fall on lattices as far as 300, which means the farthest lattices affected by meteors are within 301. So we should search till 302, which is always safe.
