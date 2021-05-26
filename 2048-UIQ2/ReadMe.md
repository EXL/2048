2048-UIQ2
=========

// TODO:

## Build

```bat
unix2dos src/wsd/*
unix2dos 2048-UIQ2/*

devices -setdefault @UIQ_21:com.symbian.UIQ
bldmake bldfiles
abld clean
abld build wins udeb
abld build armi urel
abld build arm4 urel
abld build thumb urel
epoc
epoc -urel
makesis 2048-UIQ2.pkg
```
