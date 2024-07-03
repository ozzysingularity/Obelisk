# Explanation

Range | Semantic
:-: | :-:
00-09   | CarryRange
10-19   | PreAlphaRelease
20-49   | AlphaRelease
50-89   | BetaRelease
90-99   | ReleaseCandidate
100+    | FullRelease

SemVer    | My Version Scheme | Explanation
:-:       |:-:                |:-
v1.0      | 100
v1.1      | 101
v1.0-a1   | 20
v1.0-a5   | 24
v1.0-b1   | 50
v1.0-b3   | 52
v1.0-rc1  | 90
v1.0-rc8  | 97
v1.0-rc11 | 90.1              | When an overflow occurs, add a carry number and reset the number
v2.0      | 200
v2.0-b1   | 100.50

For instance, a the first beta release for Obelisk is 'Obelisk 50.0'.
The above is equivelent to '1.0-b1' in SemVer.

Version 1.0 would be 100.0, 1.1 is 101.

# Why do I use this?

The answers simple, because I want to. It's nice to make something of my own,
which is why I made a build system instead of just using GNU Make or even the Zig Build System.
Making this project taught me things about programming that I didn't know before, and I think it's
kind of nice.
