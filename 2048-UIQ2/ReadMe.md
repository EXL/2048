2048-UIQ2
=========

// TODO:

```bat
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
