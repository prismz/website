all:
	cd hsg && runhaskell Main.hs

debug:
	cd hsg && watch runhaskell Main.hs
