#include "paddle_engine.h"
#include <iostream>
#include <vector>
#include <winerror.h>

#include <include/args.h>
#include <include/paddleocr.h>
#include <include/paddlestructure.h>
using namespace PaddleOCR;

int PaddleEngine::initRecognizer(std::string det_model_path, std::string rec_model_path, std::string cls_model_path)
{
	int ret = ERROR_SUCCESS;
	FLAGS_det_model_dir = det_model_path;
	FLAGS_rec_model_dir = rec_model_path;
	FLAGS_cls_model_dir = cls_model_path;
	recognizer = new PPOCR();
	structureDetector = new PaddleStructure();
	return ret;
}

int PaddleEngine::configRecognizer(std::string opt)
{
	int ret = ERROR_SUCCESS;
	int argc = 2;
	std::cout << "opt : " << opt << std::endl;
	char* argvalue = new char[opt.length() + 1];
	strcpy(argvalue, opt.c_str());
	char ** argv = new char*[2]{"", argvalue };
	google::ParseCommandLineFlags(&argc, &argv, true);
	std::cout << "FLAGS_rec_char_dict_path : " << FLAGS_rec_char_dict_path << std::endl;
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

int PaddleEngine::predict(cv::Mat img, std::string &jsonResult)
{
	int ret = ERROR_SUCCESS;
	PPOCR* ppocr = static_cast<PPOCR*>(recognizer);
	std::vector<OCRPredictResult> ocrPredictResult = ppocr->ocr(img, true, true, false);
	Utility::VisualizeBboxes(img, ocrPredictResult, "output/tmp.jpg");
	jsonResult = Utility::OCRPredictResult2JsonStr(ocrPredictResult);
	return ret;
}

int PaddleEngine::structure(cv::Mat img) {
	PaddleStructure* ppStructure = static_cast<PaddleStructure*>(structureDetector);

    std::vector<StructurePredictResult> structure_results = ppStructure->structure(img, false, true, false);

    for (int j = 0; j < structure_results.size(); j++) {
      std::cout << j << "\ttype: " << structure_results[j].type
                << ", region: [";
      std::cout << structure_results[j].box[0] << ","
                << structure_results[j].box[1] << ","
                << structure_results[j].box[2] << ","
                << structure_results[j].box[3] << "], score: ";
      std::cout << structure_results[j].confidence << ", res: " << std::endl;

		if (structure_results[j].type == "table") {
			std::cout << structure_results[j].html;
			Utility::VisualizeBboxes(img, structure_results[j],"output/tmp.jpg");
		} else {
			std::cout << "count of ocr result is : "
						<< structure_results[j].text_res.size() << std::endl;
			if (structure_results[j].text_res.size() > 0) {
				std::cout << "********** print ocr result "
						<< "**********" << std::endl;
				Utility::print_result(structure_results[j].text_res);
				std::cout << "********** end print ocr result "
						<< "**********" << std::endl;
			}
		}
    
	}
}