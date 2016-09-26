// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW_quantize:
//
// Quantize I1 to specified number of levels. Apply dither if flag is set.
// Output is in I2.
//
// Written by: MOFIZUR RAHMAN, JUN LI, 2016
//
void
HW_quantize(ImagePtr I1, int levels, bool dither, ImagePtr I2)
{
	IP_copyImageHeader(I1, I2);
	int w = I1->width ();
	int h = I1->height();
	int total = w * h;

	double scale = (double)MXGRAY/levels;
	double bias = scale/2;
	int i, lut[MXGRAY];
	for(i=0; i<MXGRAY; ++i) {
		lut[i] = (scale *  (int)(i/scale)) + bias;
	}
	if(!dither){
		int type;
		ChannelPtr<uchar> p1, p2, endd;
		for(int ch = 0; IP_getChannel(I1, ch, p1, type); ch++) {
			IP_getChannel(I2, ch, p2, type);
			for(endd = p1 + total; p1<endd;) *p2++ = lut[*p1++];
		}
	}else{
		int type;
		int s = 0;
		ChannelPtr<uchar> p1, p2;
		for(int ch = 0; IP_getChannel(I1, ch, p1, type); ch++) {
			IP_getChannel(I2, ch, p2, type);
			for(int y =0; y<h;y++){
				if(y%2) s=1;
				else s = -1;
				for(int x = 0; x<w; x++, s*= -1){
					int j = ((double)rand()/RAND_MAX)*bias*s + *p1++;
					*p2++ = lut[CLIP(j, 0, MaxGray)];
				}
			}
		}

	}

}
