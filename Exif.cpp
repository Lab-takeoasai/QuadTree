//. exif.java
//. K.Kimura(Programmer K) @ IBM Software Group, Japan.
//	Exif.cpp
//	Complied into c++ by Takeo Asai, Ikeuchi Lab

#include "Exif.hpp"

/*
int main (int argc, char const *argv[])
{
	for ( int i = 0; i < 1000000; i++ ) {
		ExifJPEG exif = ExifJPEG("/Users/takeo/Desktop/image.jpg");
		exif.getLatitude();
//	printf("(%g, %g)", exif.getLatitude(), exif.getLongitude());
	}
	
	return 0;
}
*/

ExifJPEG::ExifJPEG(std::string filename) {
	this->filename = filename;
	this->isCalculated = false;
}

double ExifJPEG::getLongitude() {
	this->calculate();
	return this->longitude;
}

double ExifJPEG::getLatitude() {
	this->calculate();
	return this->latitude;
}

double ExifJPEG::getX() {
    return this->getLatitude();
}

double ExifJPEG::getY() {
    return this->getLongitude();
}


//	Privates:
	
static const int kEXIF_HEADER_SIZE = 1024;

//	3.2GHz i3 4GB -> 27.5sec / 1,000,000times
//	to speed up, reduce the size exif_header_size
void ExifJPEG::calculate() {
	if ( !this->isCalculated ) {
		std::ifstream ifs;
		char buffer[kEXIF_HEADER_SIZE];
		
		ifs.open(this->filename.c_str(), std::ios::in | std::ios::binary);
		ifs.read(buffer, kEXIF_HEADER_SIZE);
		
					if ( kEXIF_HEADER_SIZE > -1 ) {
						char buf[kEXIF_HEADER_SIZE];
						int bytedata[kEXIF_HEADER_SIZE];
						for ( int i = 0; i < kEXIF_HEADER_SIZE; i ++ ) {
							buf[i] = buffer[i];
							bytedata[i] = ( 0xff & buf[i] );
						}

						bool b = true;
						int prev = 0x00;
						for ( int i = 2; i < kEXIF_HEADER_SIZE && b; i ++ ) {
							if ( prev == 0xff ) {
								int sz = 256 * bytedata[i+1] + bytedata[i+2];
								if ( bytedata[i] == 0xe1 ) {
									bool isMot = true;
									int offset = 0;
									i ++;
									i += 2;
									i += 6;

									if ( bytedata[i] == 0x4d ) {
										isMot = true;
									} else if ( bytedata[i] == 0x49 ) {
										isMot = false;
									}

									offset = isMot ?
											16777216 * bytedata[i+4] + 65536 * bytedata[i+5] + 256 * bytedata[i+6] + bytedata[i+7] :
											16777216 * bytedata[i+7] + 65536 * bytedata[i+6] + 256 * bytedata[i+5] + bytedata[i+4];

									//. IFD
									int num_dir = isMot ?
											256 * bytedata[i+offset] + bytedata[i+offset+1] :
											256 * bytedata[i+offset+1] + bytedata[i+offset];
									offset += 2;
									for( int j = 0; j < num_dir && b; j ++ ) {
										int tag = isMot ?
												256 * bytedata[i+offset] + bytedata[i+offset+1] :
												256 * bytedata[i+offset+1] + bytedata[i+offset];

										if ( tag == 34853 ) {
											float lat = 0.0f, lng = 0.0f;
											int latn = 1, lngn = 1;
											int data = isMot ?
													16777216 * bytedata[i+offset+8] + 65536 * bytedata[i+offset+9] + 256 * bytedata[i+offset+10] + bytedata[i+offset+11] :
													16777216 * bytedata[i+offset+11] + 65536 * bytedata[i+offset+10] + 256 * bytedata[i+offset+9] + bytedata[i+offset+8];
											offset = data;
											b = false;

											int gps_num_dir = isMot ?
													256 * bytedata[i+offset] + bytedata[i+offset+1] :
													256 * bytedata[i+offset+1] + bytedata[i+offset];
											offset += 2;
											for ( int k = 0; k < gps_num_dir; k ++ ) {
												int gps_tag = isMot ?
														256 * bytedata[i+offset] + bytedata[i+offset+1] :
														256 * bytedata[i+offset+1] + bytedata[i+offset];

												int gps_type = isMot ?
														256 * bytedata[i+offset+2] + bytedata[i+offset+3] :
														256 * bytedata[i+offset+3] + bytedata[i+offset+2];
												int gps_num_data = isMot ?
														16777216 * bytedata[i+offset+4] + 65536 * bytedata[i+offset+5] + 256 * bytedata[i+offset+6] + bytedata[i+offset+7] :
														16777216 * bytedata[i+offset+7] + 65536 * bytedata[i+offset+6] + 256 * bytedata[i+offset+5] + bytedata[i+offset+4];
												int gps_data = ( gps_type == 5 && isMot ) ? //isMot ? (K.Kimura 2010/Sep/26)
														16777216 * bytedata[i+offset+8] + 65536 * bytedata[i+offset+9] + 256 * bytedata[i+offset+10] + bytedata[i+offset+11] :
														16777216 * bytedata[i+offset+11] + 65536 * bytedata[i+offset+10] + 256 * bytedata[i+offset+9] + bytedata[i+offset+8];
												
												std::string gps_data_s = toString(gps_data);
												if ( gps_type == 2 ) {
													gps_data_s = "" + ( char )gps_data;
												} else if ( gps_type == 5 ) {
													double f = 0.0;
													for( int m = 0; m < gps_num_data; m ++ ) {
														int f1 = isMot ?
																16777216 * bytedata[i+8*m+gps_data] + 65536 * bytedata[i+8*m+gps_data+1] + 256 * bytedata[i+8*m+gps_data+2] + bytedata[i+8*m+gps_data+3] :
																16777216 * bytedata[i+8*m+gps_data+3] + 65536 * bytedata[i+8*m+gps_data+2] + 256 * bytedata[i+8*m+gps_data+1] + bytedata[i+8*m+gps_data];
														int f2 = isMot ?
																16777216 * bytedata[i+8*m+gps_data+4] + 65536 * bytedata[i+8*m+gps_data+5] + 256 * bytedata[i+8*m+gps_data+6] + bytedata[i+8*m+gps_data+7] :
																16777216 * bytedata[i+8*m+gps_data+7] + 65536 * bytedata[i+8*m+gps_data+6] + 256 * bytedata[i+8*m+gps_data+5] + bytedata[i+8*m+gps_data+4];
														double d = ( double )f1 / ( double )f2;

														if ( m == 0 ) {
															f += d;
														} else if ( m == 1 ) {
															f += ( d / 60.0 );
														} else if ( m == 2 ) {
															f += ( d / 3600.0 );
														}
													}
													gps_data_s = toString(f);
												}

												if ( gps_tag == 1 ) {
													if ( gps_data_s == "N" ) {
														latn = 1;
													} else if ( gps_data_s == "S" ) {
														latn = -1;
													}
												} else if ( gps_tag == 2 ) {
													try{
														lat = toDouble( gps_data_s );
													} catch (char *e) {
													}
												} else if ( gps_tag == 3 ) {
													if ( gps_data_s == "E" ) {
														lngn = 1;
													} else if ( gps_data_s == "W" ) {
														lngn = -1;
													}
												} else if ( gps_tag == 4 ) {
													try{
														lng = toDouble( gps_data_s );
													} catch (char *e) {
													}
												}

												offset += 12;
											}

											lat = latn * lat;
											lng = lngn * lng;
											this->latitude = lat;
											this->longitude = lng;
										}
										offset += 12;
									}
									i += offset;
								} else {
									i += sz;
								}
								prev = 0x00;
							} else {
								prev = bytedata[i];
							}
						}
					}
		
		ifs.close();
		this->isCalculated = true;
	}
}
