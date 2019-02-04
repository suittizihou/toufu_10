#include "Renderer.h"

#include"Utility/Filepath.h"

#include<DxLib.h>
#include<cassert>
#include<sstream>
#include<iomanip>
#include"Math/Convert/Convert.h"
#include"Math/MathType.h"

Renderer::Renderer()
	: textures()
{
}

Renderer::~Renderer() {
	Clear();
}

Renderer& Renderer::GetInstance()
{
	static Renderer instance;
	return instance;
}

void Renderer::LoadTexture(Assets::Texture id, const std::string & fileName)
{
	int handle = LoadGraph((Filepath::TextureFolder + fileName).c_str());
	if (handle == -1) {
		assert(!"Failure to read the file.");
		return;
	}
	textures.emplace(id, handle);
}


void Renderer::DrawTexture(Assets::Texture id, const Vector2 & position, const Vector2 & center, const Vector2 & scale, float angle, const Color& color)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(color.a * 255.0f));
	SetDrawBright(color.r * 255.0f, color.g * 255.0f, color.b * 255.0f);
	DrawRotaGraph3(
		position.x, position.y,
		center.x, center.y,
		scale.x, scale.y,
		angle * Math::toRadian,
		textures[id],
		TRUE,
		FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	SetDrawBright(255.0f,255.0f,255.0f);
}

void Renderer::DrawRectangle(Assets::Texture id, const Vector2 & position, const Rect & rect, const Color& color)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(color.a * 255.0f));
	SetDrawBright(color.r * 255.0f, color.g * 255.0f, color.b * 255.0f);
	DrawRectGraph(
		position.x, position.y,
		rect.left, rect.top,
		rect.right, rect.bottom,
		textures[id],
		TRUE,
		FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	SetDrawBright(255.0f, 255.0f, 255.0f);
}

void Renderer::DrawNumber(Assets::Texture id, const Vector2 & position, int number, int width, int height, int digit, char fill)
{
	//参考URL:http://www.geocities.jp/hp_yamakatsu/gakuseiC_01.html

	std::stringstream ss;

	// digitの桁数に fill + numberを収める
	//例　digit = 10桁, fill = '$', number = 1997
	//　　$$$$$$1997
	ss << std::setw(digit) << std::setfill(fill) << number;

	std::string numStr = ss.str();

	//表示する数字分forで回す
	for (unsigned int i = 0; i < numStr.size(); ++i) {
		//スペースならもう一回
		if (numStr[i] == ' ')
			continue;

		int n = numStr[i] - '0';
		Vector2 pos(position.x + i * width, position.y);
		Rect rect(n * width, 0.0f, width, height);
		DrawRectangle(id, pos, rect);
	}
}


void Renderer::DeleteTexture(Assets::Texture id)
{
	DeleteGraph(textures[id]);
	textures.erase(id);
}

void Renderer::Clear()
{

	for (auto& id : textures) {
		DeleteGraph(id.second);
	}
	textures.clear();
}

