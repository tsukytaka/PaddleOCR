#include "paddle_engine.h"
#include <iostream>
#include <vector>
#include <winerror.h>

#include <include/args.h>
#include <include/paddleocr.h>
using namespace PaddleOCR;

int PaddleEngine::initRecognizer(std::string model_path)
{
	int ret = ERROR_SUCCESS;
	FLAGS_rec_model_dir = model_path;
	FLAGS_det = false;
	FLAGS_cls = false;
	recognizer = new PPOCR();
	return ret;
}

int PaddleEngine::configRecognizer(std::string opt)
{
	int ret = ERROR_SUCCESS;
	int argc = 2;
	std::cout << "opt : " << opt << endl;
	char* argvalue = new char[opt.length() + 1];
	strcpy(argvalue, opt.c_str());
	char ** argv = new char*[2]{"", argvalue };
	google::ParseCommandLineFlags(&argc, &argv, true);
	std::cout << "FLAGS_rec_char_dict_path : " << FLAGS_rec_char_dict_path << endl;
	return ret;
}

int PaddleEngine::readText(cv::Mat img, std::string &text, double &score, bool det, bool rec, bool cls)
{
	int ret = ERROR_SUCCESS;
	PPOCR* ppocr = static_cast<PPOCR*>(recognizer);
	text = "";
	score = -1;
	ret = ppocr->ocr(img, text, score, det, rec, cls);

	return ret;
}