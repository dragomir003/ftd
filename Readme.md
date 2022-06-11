```
                __ _      _
                / _| |_ __| |
                | |_| __/ _` |
                |  _| || (_| |
                |_|  \__\__,_|
```

# FTD

FTD is a functional style extension of ```C++```'s std.

It should mimic ```Haskell```'s standard library, but be as efficient as possible
and not blindly copy ```Haskell```'s design choices even when they do not actualy work in C++.

This library aims to extend ```C++```'s standard library by not using any
external dependencies.
For example: adding ```fmap``` to ```std::vector``` instead of defining new container with fmap
support.

# Showcases

The project is currently in planning faze.

# To-Do

## Basic functional concepts

- curry/uncurry
- flip
- sum and product types
- Foldable, Semigroup, Monoid
- and so on...

## Functional style

- Functors, Applicatives, Monads...