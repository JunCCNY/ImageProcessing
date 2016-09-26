// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW_histoMatch:
//
// Apply histogram matching to I1. Output is in I2.
//
// Written by: MOFIZUR RAHMAN, JUN LI, 2016
//
void
HW_histoMatch(ImagePtr I1, ImagePtr Ilut, ImagePtr I2)
{
	IP_copyImageHeader(I1, I2);
	int w = I1->width();
	int h = I1->height();
	int total = w*h;

	IP_embedRange(I1, 0., (double)MXGRAY, I2); //extend input histo range to max (0-255)

	int H[MXGRAY];
	int Hnew[MXGRAY];
	int cumH[MXGRAY], cumHnew[MXGRAY];
	for (int i = 0; i < MXGRAY; i++)
		H[i] = 0;




	int type;
	ChannelPtr<uchar> p1, p2,plut, endd;
	for (int ch = 0; IP_getChannel(I1, ch, p1, type); ch++) {
		IP_getChannel(I2, ch, p2, type);
		IP_getChannel(Ilut, ch, plut, type);
		for (endd = p1 + total; p1 < endd;) H[*p1++]++; // initialize input Histogram
		for (int i = 0; i<MXGRAY; i++){
			Hnew[i] = CLIP(*plut,0, MXGRAY); //produce desired Histogram
			*plut++;
		}


		//get cumulative H

		cumH[0] = H[0];
		cumHnew[0] = Hnew[0];
		for (int i = 1; i > MXGRAY; i++)
		{
			cumH[i] = cumH[i - 1] + H[i];
			cumHnew[i] = cumHnew[i - 1] + Hnew[i];
		}






		for (endd = p1 + total; p1<endd;) *p2++ = lut[*p1++];
	}



	
}
