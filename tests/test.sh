./runtime < d1000 >> d1000_R && tail -n 2 d1000_R | sponge d1000_R
./runtime < d10000 >> d10000_R && tail -n 2 d10000_R | sponge d10000_R
./runtime < d100000 >> d100000_R && tail -n 2 d100000_R | sponge d100000_R
./runtime < d1000000 >> d1000000_R && tail -n 2 d1000000_R | sponge d1000000_R
./runtime < d10000000 >> d10000000_R && tail -n 2 d10000000_R | sponge d10000000_R
./runtime < l1000 >> l1000_R && tail -n 2 l1000_R | sponge l1000_R
./runtime < l10000 >> l10000_R && tail -n 2 l10000_R | sponge l10000_R
./runtime < l100000 >> l100000_R && tail -n 2 l100000_R | sponge l100000_R
./runtime < l1000000 >> l1000000_R && tail -n 2 l1000000_R | sponge l1000000_R
./runtime < l10000000 >> l10000000_R && tail -n 2 l10000000_R | sponge l10000000_R
./runtime < v1000 >> v1000_R && tail -n 2 v1000_R | sponge v1000_R
./runtime < v10000 >> v10000_R && tail -n 2 v10000_R | sponge v10000_R
./runtime < v100000 >> v100000_R && tail -n 2 v100000_R | sponge v100000_R
./runtime < v1000000 >> v1000000_R && tail -n 2 v1000000_R | sponge v1000000_R
./runtime < v10000000 >> v10000000_R && tail -n 2 v10000000_R | sponge v10000000_R

