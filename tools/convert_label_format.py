import json
import os
import sys

def list_files_with_extension(folder_path, extension):
    listFile = []
    for file in os.listdir(folder_path):
        if file.endswith(extension):
            listFile.append(file)
            print(os.path.join(folder_path, file))
    return listFile

def main(args):
    contentNewFormat = ""
    pathDataDir = args.data_dir
    listFiles = list_files_with_extension(pathDataDir, ".json")
    for jsonFile in listFiles:
        with open(os.path.join(pathDataDir, jsonFile)) as json_file:
            data = json.load(json_file)
        for item in data:
            print("file name: " , item["image"])
            pathImg = pathDataDir.replace("/", "\\")
            pathImg = os.path.join(pathImg, item["image"])
            contentNewFormat += pathImg
            
            infos = []
            for annotation in item["annotations"]:
                print("label: " , annotation["label"])
                print("pos: " , annotation["coordinates"])
                #convert position here
                topleft = (int(annotation["coordinates"]['x']), int(annotation["coordinates"]['y']))
                topright = (int(annotation["coordinates"]['x'] + annotation["coordinates"]['width']), int(annotation["coordinates"]['y']))
                bottomright = (int(annotation["coordinates"]['x'] + annotation["coordinates"]['width']), int(annotation["coordinates"]['y'] + annotation["coordinates"]['height']))
                bottomleft = (int(annotation["coordinates"]['x']), int(annotation["coordinates"]['y'] + annotation["coordinates"]['height']))

                #add to content here
                info = {}
                info["transcription"] = annotation["label"]
                info["points"] = [topleft, topright, bottomright, bottomleft]
                info["difficult"] = False
                infos.append(info)
            contentNewFormat += "\t" + json.dumps(infos) + "\n"
            print("contentNewFormat: " , contentNewFormat)

    #save content to file here
    with open(pathDataDir + "/output.txt", 'w') as f:
        f.write(contentNewFormat)
    return 0

def parse_args():
    import argparse
    parser = argparse.ArgumentParser(description="args for data converted")
    parser.add_argument("--data_dir", type=str, required=True)
    parser.add_argument("--output_file", type=str, default='./annotation_file.txt')
    args = parser.parse_args()
    return args

if __name__ == '__main__':
    args = parse_args()
    main(args)