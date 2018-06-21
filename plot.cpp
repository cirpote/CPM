#include "CPM.h"
#include "OpticFlowIO.h"

std::vector< vector<int> > ReadMatches(const char *filename)
{

    std::ifstream FILE(filename);
    std::string line;
    std::vector< vector<int> > optical_flow;
    while (std::getline(FILE, line)){
        std::vector<int> curr_line;
        std::string offset_cpy = line;
		std::string delimiter = " ";
		size_t pos = 0;
		std::string token;
		while ((pos = offset_cpy.find(delimiter)) != std::string::npos) {
			token = offset_cpy.substr(0, pos);
			curr_line.push_back( atof(token.c_str()) );
			offset_cpy.erase(0, pos + delimiter.length());
		}
		curr_line.push_back( atof(offset_cpy.c_str()) );
        optical_flow.push_back(curr_line);
    }

    FILE.close ();
    return optical_flow;
}

int main(int argc, char** argv)
{
	/*if (argc < 4){
		printf("USAGE: CPM image1 image2 inMatchText\n");
		return -1;
	}*/

	cv::Mat img1, img2, img3;

	img1 = cv::imread("../imgs/fixed_cloud_color.png", CV_LOAD_IMAGE_UNCHANGED);
	img2 = cv::imread("../imgs/moving_cloud_color.png", CV_LOAD_IMAGE_UNCHANGED);

	//cv::cvtColor(img1, img1, CV_GRAY2RGB);
	//cv::cvtColor(img2, img2, CV_GRAY2RGB);

    std::cout << "Reading Input Text File: " << "../imgs/output_rgb" << "\n";
    std::vector< vector<int> > optical_flow = ReadMatches("../imgs/output_rgb");

	std::cout << "matches size: " << optical_flow.size() << "\n";

    /*for(unsigned int iter = 0; iter < optical_flow.size(); ++iter)
        std::cout << optical_flow[iter][0] << " " << optical_flow[iter][1] << " " <<
                     optical_flow[iter][2] << " " << optical_flow[iter][3] << "\n";*/

    cv::Mat drawImg( cv::Size(2000,1000), CV_8UC3, cv::Scalar(0,0,0) );
    img1.copyTo( drawImg( cv::Rect(0, 0, 1000, 1000) )  );
    img2.copyTo( drawImg( cv::Rect(1000, 0, 1000, 1000) )  );

    for( unsigned int iter = 0; iter < optical_flow.size(); ++iter ) {
        if( !(optical_flow[iter][0] % 10) && !(optical_flow[iter][1] % 10) ) 
            cv::line( drawImg, cv::Point(optical_flow[iter][0], optical_flow[iter][1]), cv::Point(optical_flow[iter][2]+1000, optical_flow[iter][3]), cv::Scalar(0, 255, 0));
        
    }

    cv::imshow("optical_flow", drawImg);
    cv::waitKey(0);

	return 0;
}