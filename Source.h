#pragma once

#include "DxLib.h"
#include <string>
#include <unordered_map>

#include <cassert>

class Graph{
public:

	//シングルトン
	static Graph& get(){
		static Graph inst;
		return inst;
	}

	static int handle(std::string name){
		return get().handlemap.at(name);
	}

private:
	std::unordered_map<std::string, int> handlemap;

	Graph()
	{
		init();
	}

	void init(){
		LoadToMap("bar_back");
		LoadToMap("bar_hp");
		LoadToMap("bar_sima64_40");
		LoadToMap("bar_stone");
		LoadToMap("bar_wback");
		LoadToMap("bar_wmain");
		LoadToMap("bar_wsub");
		LoadToMap("block");
		LoadToMap("blood01");
		LoadToMap("byyagiri");
		LoadToMap("chainsaw");
		LoadToMap("dot32");
		LoadToMap("dot32_black");
		LoadToMap("enemycursor");
		LoadToMap("firebase");
		LoadToMap("floor01");
		LoadToMap("gra32");
		LoadToMap("gun");
		LoadToMap("icebase");
		LoadToMap("icon_frame");
		LoadToMap("icon_sister");
		LoadToMap("light01");
		LoadToMap("mousecursor");
		LoadToMap("mousecursor2");
		LoadToMap("rect32");
		LoadToMap("rect32_black");
		LoadToMap("resultback");
		LoadToMap("result_str");
		LoadToMap("ryudan");
		LoadToMap("saint_blood");
		LoadToMap("saint_foot");
		LoadToMap("slash01");
		LoadToMap("str_log_gra");
		LoadToMap("suna");
		LoadToMap("s_selectback");
		LoadToMap("s_select_bk_ef");
		LoadToMap("s_select_start");
		LoadToMap("titlebg");
		LoadToMap("title_str_exit");
		LoadToMap("title_str_start");
		LoadToMap("w_mine");
		LoadToMap("w_selectback");
		LoadToMap("w_select_bk_ef");
		LoadToMap("w_select_start");


	}

	void LoadToMap(std::string name){
		int gh;
		std::string loadname = "Images/" + name;
		gh = LoadGraph((loadname + ".png").c_str());
		if (gh != -1){
			handlemap.emplace(name, gh);
			return;
		}
		gh = LoadGraph((loadname + ".jpg").c_str());
		if (gh != -1){
			handlemap.emplace(name, gh);
			return;
		}
	}

	Graph& operator=(const Graph& a) = delete;
	Graph(const Graph& a) = delete;
};



class GraphDiv{
public:

	//シングルトン
	static GraphDiv& get(){
		static GraphDiv inst;
		return inst;
	}

	static int handle(std::string name, int num){
		return get().handlemap.at(name).arr[num];
	}

	class gh_array{
	public:
		int arr[128];
	};

private:
	std::unordered_map<std::string, gh_array> handlemap;

	GraphDiv()
	{
		init();
	}

	//分割して読み込み(pngのみ読み込み)
	void init(){
		LoadToMap("playera", 24, 6, 4, 20, 28);
		LoadToMap("zombie", 16, 16, 1, 64, 64);
		LoadToMap("icon64", 16, 4, 4, 64, 64);
		LoadToMap("weapon64", 16, 4, 4, 64, 64);
	}

	//(pngのみ読み込み)
	void LoadToMap(std::string name, int AllNum, int XNum, int YNum, int XSize, int YSize){
		std::string loadname = "Images_div/" + name;
		gh_array gh_array_;
		LoadDivGraph((loadname + ".png").c_str(), AllNum, XNum, YNum, XSize, YSize, &gh_array_.arr[0]);
		handlemap.emplace(name, gh_array_);
	}

	GraphDiv& operator=(const GraphDiv& a) = delete;
	GraphDiv(const GraphDiv& a) = delete;
};



class Sound{
public:

	//シングルトン
	static Sound& get(){
		static Sound inst;
		return inst;
	}

	static int handle(std::string name){
		return get().handlemap.at(name);
	}

	//一回だけ再生
	static void playback(std::string name){
		PlaySoundMem(get().handle(name), DX_PLAYTYPE_BACK);
	}

	//ループ再生
	static void playloop(std::string name){
		PlaySoundMem(get().handle(name), DX_PLAYTYPE_LOOP);
	}

	//BGM再生 BGMは常時一つだけ
	static void playbgm(std::string name){
		StopSoundMem(get().bgmhandle);
		get().bgmhandle = get().handle(name);
		PlaySoundMem(get().bgmhandle, DX_PLAYTYPE_LOOP);
	}

	//一度だけ再生するBGMを再生 BGMは常時一つだけ
	static void playbgm_once(std::string name){
		StopSoundMem(get().bgmhandle);
		get().bgmhandle = get().handle(name);
		PlaySoundMem(get().bgmhandle, DX_PLAYTYPE_BACK);
	}

	//再生中の音をすべて停止
	static void stopall(){
		for (auto i : get().handlemap){
			StopSoundMem(i.second);
		}
	}

	//指定した音の再生を停止
	static void stopone(std::string name){
		StopSoundMem(get().handle(name));
	}

private:
	std::unordered_map<std::string, int> handlemap;
	int bgmhandle;

	Sound()
	{
		bgmhandle = -1;
		init();
	}

	void init(){
		LoadToMap("bomb01");
		LoadToMap("chainsaw");
		LoadToMap("dying");
		LoadToMap("enemydead");
		LoadToMap("flamethrow");
		LoadToMap("glasscrash");
		LoadToMap("machinegun");
		LoadToMap("menucancel");
		LoadToMap("menuenter");
		LoadToMap("menumove");
		LoadToMap("put01");
		LoadToMap("railgun");
		LoadToMap("reloadend");
		LoadToMap("reloadstart");
		LoadToMap("result");
		LoadToMap("rifle");
		LoadToMap("select");
		LoadToMap("shotgun");
		LoadToMap("stagebgm");
		LoadToMap("stageend");
		LoadToMap("stagestart");
		LoadToMap("swing02");
		LoadToMap("title");
		LoadToMap("zusa");

	}

	void LoadToMap(std::string name){
		int sh;
		std::string loadname = "Sounds/" + name;
		sh = LoadSoundMem((loadname + ".wav").c_str());
		if (sh != -1){
			handlemap.emplace(name, sh);
			return;
		}
		sh = LoadSoundMem((loadname + ".ogg").c_str());
		if (sh != -1){
			handlemap.emplace(name, sh);
			return;
		}
		sh = LoadSoundMem((loadname + ".mp3").c_str());
		if (sh != -1){
			handlemap.emplace(name, sh);
			return;
		}
		OutputDebugString(("\n" + name + " is not exist\n").c_str());
		//assert(1 == 0 && "sound file is not exist" && name.c_str());
	}

	Sound& operator=(const Sound& a) = delete;
	Sound(const Sound& a) = delete;

};



class Font{
public:

	//シングルトン
	static Font& get(){
		static Font inst;
		return inst;
	}

	static int handle(std::string name){
		return get().handlemap.at(name);
	}

private:
	std::unordered_map<std::string, int> handlemap;

	Font()
	{
		init();
	}

	void init(){
		handlemap.emplace("SegoeUI16", CreateFontToHandle("Segoe UI", 16, 5, DX_FONTTYPE_ANTIALIASING_4X4));
		handlemap.emplace("SegoeUI20", CreateFontToHandle("Segoe UI", 20, 5, DX_FONTTYPE_ANTIALIASING_4X4));
		handlemap.emplace("SegoeUI40", CreateFontToHandle("Segoe UI", 40, 5, DX_FONTTYPE_ANTIALIASING_4X4));
	}

	void LoadToMap(std::string name, int Size, int Thick, int FontType){
		int fh = CreateFontToHandle(name.c_str(), Size, Thick, FontType);
		handlemap.emplace(name.c_str(), fh);
	}

	Font& operator=(const Font& a) = delete;
	Font(const Font& a) = delete;

};


