#include "paddle_engine.h"
#include <iostream>
#include <vector>
#include <winerror.h>

#include <include/args.h>
#include <include/paddleocr.h>
using namespace PaddleOCR;

int PaddleEngine::initRecognizer(std::string det_model_path, std::string rec_model_path, std::string cls_model_path)
{
	int ret = ERROR_SUCCESS;
	FLAGS_det_model_dir = det_model_path;
	FLAGS_rec_model_dir = rec_model_path;
	FLAGS_cls_model_dir = cls_model_path;
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
	if (img.cols < 5 || img.rows < 5)
	{
		ret = ERROR_DATA_NOT_ACCEPTED;
	}
	if (ret == ERROR_SUCCESS)
	{
		PPOCR* ppocr = static_cast<PPOCR*>(recognizer);
		text = "";
		score = -1;
		ret = ppocr->ocr(img, text, score, det, rec, cls);
	}
	return ret;
}