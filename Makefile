VISUAL_FLAGS=/GS /GL /W3 /Gy /Zc:wchar_t /Zi /Gm- /O2 /Zc:inline /fp:precise /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_UNICODE" /D "UNICODE" /WX- /Zc:forScope /Gd /Oi /MD /EHsc /Ot

cf1_k0: cf1.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=0 cf1.cpp /link /out:cf1_k0.exe

cf1_k1: cf1.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=1 cf1.cpp /link /out:cf1_k1.exe

cf1_k2: cf1.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=2 cf1.cpp /link /out:cf1_k2.exe

cf1_k3: cf1.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=3 cf1.cpp /link /out:cf1_k3.exe

cf1_k4: cf1.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=4 cf1.cpp /link /out:cf1_k4.exe

cf1: cf1_k0 cf1_k1 cf1_k2 cf1_k3 cf1_k4


cf1_gram_k0: cf1_gram.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=0 cf1_gram.cpp /link /out:cf1_gram_k0.exe

cf1_gram_k1: cf1_gram.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=1 cf1_gram.cpp /link /out:cf1_gram_k1.exe

cf1_gram_k2: cf1_gram.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=2 cf1_gram.cpp /link /out:cf1_gram_k2.exe

cf1_gram_k3: cf1_gram.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=3 cf1_gram.cpp /link /out:cf1_gram_k3.exe

cf1_gram_k4: cf1_gram.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=4 cf1_gram.cpp /link /out:cf1_gram_k4.exe

cf1_gram: cf1_gram_k0 cf1_gram_k1 cf1_gram_k2 cf1_gram_k3 cf1_gram_k4

cf1all: cf1_gram cf1

cf2_k0: cf2.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=0 cf2.cpp /link /out:cf2_k0.exe

cf2_k1: cf2.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=1 cf2.cpp /link /out:cf2_k1.exe

cf2_k2: cf2.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=2 cf2.cpp /link /out:cf2_k2.exe

cf2_k3: cf2.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=3 cf2.cpp /link /out:cf2_k3.exe

cf2_k4: cf2.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=4 cf2.cpp /link /out:cf2_k4.exe

cf2: cf2_k0 cf2_k1 cf2_k2 cf2_k3 cf2_k4


cf2_simd_k0: cf2_simd.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=0 cf2_simd.cpp /link /out:cf2_simd_k0.exe

cf2_simd_k1: cf2_simd.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=1 cf2_simd.cpp /link /out:cf2_simd_k1.exe

cf2_simd_k2: cf2_simd.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=2 cf2_simd.cpp /link /out:cf2_simd_k2.exe

cf2_simd_k3: cf2_simd.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=3 cf2_simd.cpp /link /out:cf2_simd_k3.exe

cf2_simd_k4: cf2_simd.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=4 cf2_simd.cpp /link /out:cf2_simd_k4.exe

cf2_simd: cf2_simd_k0 cf2_simd_k1 cf2_simd_k2 cf2_simd_k3 cf2_simd_k4


cf2_simd_gram_k0: cf2_simd_gram.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=0 cf2_simd_gram.cpp /link /out:cf2_simd_gram_k0.exe

cf2_simd_gram_k1: cf2_simd_gram.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=1 cf2_simd_gram.cpp /link /out:cf2_simd_gram_k1.exe

cf2_simd_gram_k2: cf2_simd_gram.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=2 cf2_simd_gram.cpp /link /out:cf2_simd_gram_k2.exe

cf2_simd_gram_k3: cf2_simd_gram.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=3 cf2_simd_gram.cpp /link /out:cf2_simd_gram_k3.exe

cf2_simd_gram_k4: cf2_simd_gram.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=4 cf2_simd_gram.cpp /link /out:cf2_simd_gram_k4.exe

cf2_simd_gram: cf2_simd_gram_k0 cf2_simd_gram_k1 cf2_simd_gram_k2 cf2_simd_gram_k3 cf2_simd_gram_k4


cf2_skip_k0: cf2_skip.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=0 cf2_skip.cpp /link /out:cf2_skip_k0.exe

cf2_skip_k1: cf2_skip.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=1 cf2_skip.cpp /link /out:cf2_skip_k1.exe

cf2_skip_k2: cf2_skip.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=2 cf2_skip.cpp /link /out:cf2_skip_k2.exe

cf2_skip_k3: cf2_skip.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=3 cf2_skip.cpp /link /out:cf2_skip_k3.exe

cf2_skip_k4: cf2_skip.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=4 cf2_skip.cpp /link /out:cf2_skip_k4.exe

cf2_skip : cf2_skip_k0 cf2_skip_k1 cf2_skip_k2 cf2_skip_k3 cf2_skip_k4


cf2_skip_simd_k0: cf2_skip_simd.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=0 cf2_skip_simd.cpp /link /out:cf2_skip_simd_k0.exe

cf2_skip_simd_k1: cf2_skip_simd.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=1 cf2_skip_simd.cpp /link /out:cf2_skip_simd_k1.exe

cf2_skip_simd_k2: cf2_skip_simd.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=2 cf2_skip_simd.cpp /link /out:cf2_skip_simd_k2.exe

cf2_skip_simd_k3: cf2_skip_simd.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=3 cf2_skip_simd.cpp /link /out:cf2_skip_simd_k3.exe

cf2_skip_simd_k4: cf2_skip_simd.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=4 cf2_skip_simd.cpp /link /out:cf2_skip_simd_k4.exe

cf2_skip_simd : cf2_skip_simd_k0 cf2_skip_simd_k1 cf2_skip_simd_k2 cf2_skip_simd_k3 cf2_skip_simd_k4


cf2_skip_simd_gram_k0: cf2_skip_simd_gram.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=0 cf2_skip_simd_gram.cpp /link /out:cf2_skip_simd_gram_k0.exe

cf2_skip_simd_gram_k1: cf2_skip_simd_gram.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=1 cf2_skip_simd_gram.cpp /link /out:cf2_skip_simd_gram_k1.exe

cf2_skip_simd_gram_k2: cf2_skip_simd_gram.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=2 cf2_skip_simd_gram.cpp /link /out:cf2_skip_simd_gram_k2.exe

cf2_skip_simd_gram_k3: cf2_skip_simd_gram.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=3 cf2_skip_simd_gram.cpp /link /out:cf2_skip_simd_gram_k3.exe

cf2_skip_simd_gram_k4: cf2_skip_simd_gram.cpp common.h
	cl $(VISUAL_FLAGS) /DK_DIFF=4 cf2_skip_simd_gram.cpp /link /out:cf2_skip_simd_gram_k4.exe

cf2_skip_simd_gram: cf2_skip_simd_gram_k0 cf2_skip_simd_gram_k1 cf2_skip_simd_gram_k2 cf2_skip_simd_gram_k3 cf2_skip_simd_gram_k4

cf2all: cf2_skip_simd_gram cf2_skip_simd cf2_skip cf2_simd_gram cf2_simd cf2 
	
all: cf1all cf2all

clean:
	del *.exe *.pdb *.obj