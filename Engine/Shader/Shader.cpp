#include "Shader.h"
#include <d3dcompiler.h>
#include "../Core/Engine.h"

namespace Blue
{
	Shader::Shader(const std::wstring& name)
		: name(name)
	{
		// ��� �߰�.
		wchar_t path[256] = { };
		swprintf_s(path, 256, L"HLSLShader/%sVertexShader.hlsl", name.c_str());

		// ���̴� ������.
		//ID3DBlob* vertexShaderBuffer = nullptr;
		auto result = D3DCompileFromFile(
			//TEXT("VertexShader.hlsl"),
			path,
			nullptr,
			nullptr,
			"main",
			"vs_5_0",
			0, 0,
			&vertexShaderBuffer, nullptr
		);

		if (FAILED(result))
		{
			MessageBoxA(
				nullptr,
				"Failed to compile vertex shader",
				"Error",
				MB_OK
			);

			__debugbreak();
		}

		// ��ġ ��ü ������.
		ID3D11Device& device = Engine::Get().Device();

		// ���̴� ����.
		result = device.CreateVertexShader(
			vertexShaderBuffer->GetBufferPointer(),
			vertexShaderBuffer->GetBufferSize(),
			nullptr,
			&vertexShader
		);

		if (FAILED(result))
		{
			MessageBoxA(
				nullptr,
				"Failed to create vertex shader",
				"Error",
				MB_OK
			);

			__debugbreak();
		}

		// �Է� ���̾ƿ�.
		// ���� ���̴��� ������ ���� �����Ͱ� ��� ������� �˷���.
		D3D11_INPUT_ELEMENT_DESC inputDesc[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		result = device.CreateInputLayout(
			inputDesc,
			_countof(inputDesc),
			vertexShaderBuffer->GetBufferPointer(),
			vertexShaderBuffer->GetBufferSize(),
			&inputlayout
		);

		if (FAILED(result))
		{
			MessageBoxA(
				nullptr,
				"Failed to create input layout",
				"Error",
				MB_OK
			);

			__debugbreak();
		}

		// �ȼ� ���̴� ������/����.
		// �� ���ҽ� ���ε�.
		// ���̴� ������.
		//ID3DBlob* pixelShaderBuffer = nullptr;
		swprintf_s(path, 256, L"HLSLShader/%sPixelShader.hlsl", name.c_str());
		result = D3DCompileFromFile(
			//TEXT("PixelShader.hlsl"),
			path,
			nullptr,
			nullptr,
			"main",
			"ps_5_0",
			0, 0,
			&pixelShaderBuffer, nullptr
		);

		if (FAILED(result))
		{
			MessageBoxA(
				nullptr,
				"Failed to compile pixel shader",
				"Error",
				MB_OK
			);

			__debugbreak();
		}

		// ���̴� ����.
		result = device.CreatePixelShader(
			pixelShaderBuffer->GetBufferPointer(),
			pixelShaderBuffer->GetBufferSize(),
			nullptr,
			&pixelShader
		);

		if (FAILED(result))
		{
			MessageBoxA(
				nullptr,
				"Failed to create pixel shader",
				"Error",
				MB_OK
			);

			__debugbreak();
		}
	}

	Shader::~Shader()
	{
		// DX ���ҽ� ����.
		if (inputlayout)
		{
			inputlayout->Release();
		}
		if (vertexShader)
		{
			vertexShader->Release();
		}
		if (vertexShaderBuffer)
		{
			vertexShaderBuffer->Release();
		}
		if (pixelShader)
		{
			pixelShader->Release();
		}
		if (pixelShaderBuffer)
		{
			pixelShaderBuffer->Release();
		}
	}

	void Shader::Bind()
	{
		// ��ġ ����(DeviceContext) ������.
		static ID3D11DeviceContext& context = Engine::Get().Context();

		// �Է� ���̾ƿ� ����.
		context.IASetInputLayout(inputlayout);

		// ������ ��� ����.
		context.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// ���̴� ����.
		context.VSSetShader(vertexShader, nullptr, 0);
		context.PSSetShader(pixelShader, nullptr, 0);
	}
}