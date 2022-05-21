//
// 
//for (auto cv : m_vCube)
//{
//	//int CubeIndex[12][3] = { {0,1,2}, {0,2,3}, {0,5,4}, {0,1,5}, {0,3,7}, {0,7,4}, {6,2,1}, {6,1,5}, {6,3,2}, {6,7,3}, {6,5,4}, {6,4,7} };
//	bool screenout = FALSE;
//
//	//선택 안 돼 있을 때
//	if (cv.isClicked == FALSE)
//	{
//		for (int j = 0; j < 8; j++)
//		{
//			for (int i = 0; i < COL; i++)
//			{
//				inputmat[i][0] = cv.Cube_Vertex[j][i];
//			}
//
//			cuberotateresult = matfun.Affinereturn(cv.Cube_Center, inputmat, cv.Cube_xRotate * 10, cv.Cube_yRotate * 10, cv.Cube_zRotate * 10, cv.Cube_Size, cv.Cube_xMove, cv.Cube_yMove);
//
//			for (int i = 0; i < COL; i++)
//			{
//				cv.Cube_Vertex[j][i] = cuberotateresult[i][0];
//			}
//			for (int i = 0; i < COL; i++)
//			{
//				inputmat[i][0] = cv.Cube_Vertex[j][i];
//			}
//
//			//뷰변환
//			cubeviewresult = matfun.ViewMat(inputmat, xvalue * 10, yvalue * 10, zvalue * 10, xMove, yMove, 500);
//
//			for (int i = 0; i < COL; i++)
//			{
//				inputmat[i][0] = cubeviewresult[i][0];
//			}
//
//			//카메라가 보는방향이 마이너스, 0보다 커지면 뒤쪽으로 돌아간거라서 continue;
//			if (inputmat[2][0] > 0)
//				continue;
//
//			//투영변환
//			if (m_projection == 0)
//			{
//				cubeproresult = matfun.PerProjectionMat(inputmat, inputratio, m_viewAngle, width, height);
//			}
//			else if (m_projection == 1)
//			{
//				cubeproresult = matfun.OrthoProjectionMat(inputmat, width, height);
//			}
//
//			for (int i = 0; i < COL; i++)
//			{
//				cv.Cube_Vertex[j][i] = cubeproresult[i][0];
//			}
//		}
//	}
//	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#pragma region 도형선택(큐브)
//	float Crossinput1[4][1];
//	float Crossinput2[4][1];
//	float Crossinput3[4][1];
//
//	for (int i = 0; i < 1; i++)
//	{
//		for (int i = 0; i < 4; i++)
//		{
//			Crossinput1[i][0] = cv.Cube_Vertex[0][i];
//			Crossinput2[i][0] = cv.Cube_Vertex[1][i];
//			Crossinput3[i][0] = cv.Cube_Vertex[2][i];
//		}
//		cv.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//
//		if (cv.isClicked == TRUE)
//			break;
//
//		for (int i = 0; i < 4; i++)
//		{
//			Crossinput1[i][0] = cv.Cube_Vertex[0][i];
//			Crossinput2[i][0] = cv.Cube_Vertex[2][i];
//			Crossinput3[i][0] = cv.Cube_Vertex[3][i];
//		}
//		cv.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//		if (cv.isClicked == TRUE)
//			break;
//
//
//		for (int i = 0; i < 4; i++)
//		{
//			Crossinput1[i][0] = cv.Cube_Vertex[0][i];
//			Crossinput2[i][0] = cv.Cube_Vertex[5][i];
//			Crossinput3[i][0] = cv.Cube_Vertex[4][i];
//		}
//		cv.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//		if (cv.isClicked == TRUE)
//			break;
//
//		for (int i = 0; i < 4; i++)
//		{
//			Crossinput1[i][0] = cv.Cube_Vertex[0][i];
//			Crossinput2[i][0] = cv.Cube_Vertex[1][i];
//			Crossinput3[i][0] = cv.Cube_Vertex[5][i];
//		}
//		cv.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//		if (cv.isClicked == TRUE)
//			break;
//
//
//		for (int i = 0; i < 4; i++)
//		{
//			Crossinput1[i][0] = cv.Cube_Vertex[0][i];
//			Crossinput2[i][0] = cv.Cube_Vertex[3][i];
//			Crossinput3[i][0] = cv.Cube_Vertex[7][i];
//		}
//		cv.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//		if (cv.isClicked == TRUE)
//			break;
//
//
//
//		for (int i = 0; i < 4; i++)
//		{
//			Crossinput1[i][0] = cv.Cube_Vertex[0][i];
//			Crossinput2[i][0] = cv.Cube_Vertex[7][i];
//			Crossinput3[i][0] = cv.Cube_Vertex[4][i];
//		}
//		cv.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//		if (cv.isClicked == TRUE)
//			break;
//		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		for (int i = 0; i < 4; i++)
//		{
//			Crossinput1[i][0] = cv.Cube_Vertex[6][i];
//			Crossinput2[i][0] = cv.Cube_Vertex[2][i];
//			Crossinput3[i][0] = cv.Cube_Vertex[1][i];
//		}
//		cv.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//		if (cv.isClicked == TRUE)
//			break;
//
//		for (int i = 0; i < 4; i++)
//		{
//			Crossinput1[i][0] = cv.Cube_Vertex[6][i];
//			Crossinput2[i][0] = cv.Cube_Vertex[1][i];
//			Crossinput3[i][0] = cv.Cube_Vertex[5][i];
//		}
//		cv.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//		if (cv.isClicked == TRUE)
//			break;
//
//		for (int i = 0; i < 4; i++)
//		{
//			Crossinput1[i][0] = cv.Cube_Vertex[6][i];
//			Crossinput2[i][0] = cv.Cube_Vertex[3][i];
//			Crossinput3[i][0] = cv.Cube_Vertex[2][i];
//		}
//		cv.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//		if (cv.isClicked == TRUE)
//			break;
//
//		for (int i = 0; i < 4; i++)
//		{
//			Crossinput1[i][0] = cv.Cube_Vertex[6][i];
//			Crossinput2[i][0] = cv.Cube_Vertex[7][i];
//			Crossinput3[i][0] = cv.Cube_Vertex[3][i];
//		}
//		cv.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//		if (cv.isClicked == TRUE)
//			break;
//
//		for (int i = 0; i < 4; i++)
//		{
//			Crossinput1[i][0] = cv.Cube_Vertex[6][i];
//			Crossinput2[i][0] = cv.Cube_Vertex[5][i];
//			Crossinput3[i][0] = cv.Cube_Vertex[4][i];
//		}
//		cv.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//		if (cv.isClicked == TRUE)
//			break;
//
//		for (int i = 0; i < 4; i++)
//		{
//			Crossinput1[i][0] = cv.Cube_Vertex[6][i];
//			Crossinput2[i][0] = cv.Cube_Vertex[4][i];
//			Crossinput3[i][0] = cv.Cube_Vertex[7][i];
//		}
//		cv.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//		if (cv.isClicked == TRUE)
//			break;
//
//	}
//
//	if (cv.isClicked)
//	{
//		pDC->SelectObject(checkPen);
//	}
//	else if (cv.isClicked == FALSE)
//	{
//		pDC->SelectObject(whitePen);
//	}
//	pDC->TextOut(1000, 260, str);
//
//#pragma endregion
//
//	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	//선택돼있을 때(정점을 새로 받아와서 도형을 새로 만들기)
//	if (cv.isClicked)
//	{
//		cv.Cube_Size = m_CubeSize;
//		cv.Cube_xMove = Figure_xMove;
//		cv.Cube_yMove = Figure_yMove;
//		cv.Cube_xRotate = rxvalue;
//		cv.Cube_yRotate = ryvalue;
//		cv.Cube_zRotate = rzvalue;
//
//		//str123456.Format(_T("클릭된 : %.1f"), cv.Cube_Size);
//		//pDC->TextOut(1000, 30, str123456);
//
//		float CubeVertex[8][4] = { { OriginPoint[0][0] - cv.Cube_Size, OriginPoint[1][0] + cv.Cube_Size, OriginPoint[2][0] - cv.Cube_Size, 1 },
//		{ OriginPoint[0][0] - cv.Cube_Size, OriginPoint[1][0] + cv.Cube_Size, OriginPoint[2][0] + cv.Cube_Size, 1 },
//		{ OriginPoint[0][0] + cv.Cube_Size, OriginPoint[1][0] + cv.Cube_Size, OriginPoint[2][0] + cv.Cube_Size, 1 },
//		{ OriginPoint[0][0] + cv.Cube_Size, OriginPoint[1][0] + cv.Cube_Size, OriginPoint[2][0] - cv.Cube_Size, 1 },
//		{ OriginPoint[0][0] - cv.Cube_Size, OriginPoint[1][0] - cv.Cube_Size, OriginPoint[2][0] - cv.Cube_Size, 1 },
//		{ OriginPoint[0][0] - cv.Cube_Size, OriginPoint[1][0] - cv.Cube_Size, OriginPoint[2][0] + cv.Cube_Size, 1 },
//		{ OriginPoint[0][0] + cv.Cube_Size, OriginPoint[1][0] - cv.Cube_Size, OriginPoint[2][0] + cv.Cube_Size, 1 },
//		{ OriginPoint[0][0] + cv.Cube_Size, OriginPoint[1][0] - cv.Cube_Size, OriginPoint[2][0] - cv.Cube_Size, 1 } };
//
//		////AfxMessageBox(_T("들어옴?"));	
//
//		for (int i = 0; i < 8; i++)
//		{
//			for (int j = 0; j < 4; j++)
//			{
//				cv.Cube_Vertex[i][j] = CubeVertex[i][j];
//			}
//		}
//
//		for (int j = 0; j < 8; j++)
//		{
//			for (int i = 0; i < COL; i++)
//			{
//				inputmat[i][0] = cv.Cube_Vertex[j][i];
//			}
//			for (int i = 0; i < COL; i++)
//			{
//				centerpoint[i][0] = cv.Cube_Center[i][0];
//			}
//			////SRT
//			cuberotateresult = matfun.Affinereturn(centerpoint, inputmat, cv.Cube_xRotate * 10, cv.Cube_yRotate * 10, cv.Cube_zRotate * 10, cv.Cube_Size, cv.Cube_xMove, cv.Cube_yMove);
//			for (int i = 0; i < COL; i++)
//			{
//				cv.Cube_Vertex[j][i] = cuberotateresult[i][0];
//			}
//		}
//
//
//
//		for (int j = 0; j < 8; j++)
//		{
//			for (int i = 0; i < COL; i++)
//			{
//				inputmat[i][0] = cv.Cube_Vertex[j][i];
//			}
//			//for (int i = 0; i < COL; i++)
//			//{
//			//	centerpoint[i][0] = cv.Cube_Center[i][0];
//			//}
//			////SRT
//			//cuberotateresult = matfun.Affinereturn(centerpoint, inputmat, cv.Cube_xRotate * 10, cv.Cube_yRotate * 10, cv.Cube_zRotate * 10, cv.Cube_Size, cv.Cube_xMove, cv.Cube_yMove);
//			//cuberotateresult = matfun.Affinereturn(cv.Cube_Center, inputmat, cv.Cube_xRotate * 10, cv.Cube_yRotate * 10, cv.Cube_zRotate * 10, cv.Cube_Size, cv.Cube_xMove, cv.Cube_yMove);
//			//for (int i = 0; i < COL; i++)
//			//{
//			//	cv.Cube_Vertex[j][i] = cuberotateresult[i][0];
//			//}
//			//for (int i = 0; i < COL; i++)
//			//{
//			//	inputmat[i][0] = cv.Cube_Vertex[j][i];
//			//}
//
//
//			//뷰변환
//			cubeviewresult = matfun.ViewMat(inputmat, xvalue * 10, yvalue * 10, zvalue * 10, xMove, yMove, 500);
//
//			////카메라가 보는방향이 마이너스, 0보다 커지면 뒤쪽으로 돌아간거라서 continue;
//			//if (inputmat[2][0] > 0)
//			//	continue;
//
//			for (int i = 0; i < COL; i++)
//			{
//				inputmat[i][0] = cubeviewresult[i][0];
//
//			}
//
//
//			//투영변환
//			if (m_projection == 0)
//			{
//				cubeproresult = matfun.PerProjectionMat(inputmat, inputratio, m_viewAngle, width, height);
//			}
//			else if (m_projection == 1)
//			{
//				cubeproresult = matfun.OrthoProjectionMat(inputmat, width, height);
//			}
//
//			for (int i = 0; i < COL; i++)
//			{
//				cv.Cube_Vertex[j][i] = cubeproresult[i][0];
//			}
//
//		}
//	}
//	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//	str1234567.Format(_T("%.f,%.f,%.5f"), cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1], cv.Cube_Vertex[0][2]);
//	pDC->TextOut(500, 30, str1234567);
//	str1234567.Format(_T("%.f,%.f,%.5f"), cv.Cube_Vertex[1][0], cv.Cube_Vertex[1][1], cv.Cube_Vertex[1][2]);
//	pDC->TextOut(500, 50, str1234567);
//	str1234567.Format(_T("%.f,%.f,%.5f"), cv.Cube_Vertex[2][0], cv.Cube_Vertex[2][1], cv.Cube_Vertex[2][2]);
//	pDC->TextOut(500, 70, str1234567);
//	str1234567.Format(_T("%.f,%.f,%.5f"), cv.Cube_Vertex[3][0], cv.Cube_Vertex[3][1], cv.Cube_Vertex[3][2]);
//	pDC->TextOut(500, 90, str1234567);
//	str1234567.Format(_T("%.f,%.f,%.f"), cv.Cube_Vertex[4][0], cv.Cube_Vertex[4][1], cv.Cube_Vertex[4][2]);
//	pDC->TextOut(500, 110, str1234567);
//	str1234567.Format(_T("%.f,%.f,%.f"), cv.Cube_Vertex[5][0], cv.Cube_Vertex[5][1], cv.Cube_Vertex[5][2]);
//	pDC->TextOut(500, 130, str1234567);
//	str1234567.Format(_T("%.f,%.f,%.f"), cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1], cv.Cube_Vertex[6][2]);
//	pDC->TextOut(500, 150, str1234567);
//	str1234567.Format(_T("%.f,%.f,%.f"), cv.Cube_Vertex[7][0], cv.Cube_Vertex[7][1], cv.Cube_Vertex[7][2]);
//	pDC->TextOut(500, 170, str1234567);
//
//	////////if (cv.Cube_Vertex[0][0] < 0 || cv.Cube_Vertex[0][0] > width * 2)
//	if (m_projection == 0)
//	{
//		if (cv.Cube_Vertex[0][0] < 0 || cv.Cube_Vertex[0][0] > width * 2 || cv.Cube_Vertex[0][1] < 0 || cv.Cube_Vertex[0][1] > height * 2 || cv.Cube_Vertex[0][2] < -10 || cv.Cube_Vertex[0][2] > 10 ||
//			cv.Cube_Vertex[1][0] < 0 || cv.Cube_Vertex[1][0] > width * 2 || cv.Cube_Vertex[1][1] < 0 || cv.Cube_Vertex[1][1] > height * 2 || cv.Cube_Vertex[1][2] < -10 || cv.Cube_Vertex[1][2] > 10 ||
//			cv.Cube_Vertex[2][0] < 0 || cv.Cube_Vertex[2][0] > width * 2 || cv.Cube_Vertex[2][1] < 0 || cv.Cube_Vertex[2][1] > height * 2 || cv.Cube_Vertex[2][2] < -10 || cv.Cube_Vertex[2][2] > 10 ||
//			cv.Cube_Vertex[3][0] < 0 || cv.Cube_Vertex[3][0] > width * 2 || cv.Cube_Vertex[3][1] < 0 || cv.Cube_Vertex[3][1] > height * 2 || cv.Cube_Vertex[3][2] < -10 || cv.Cube_Vertex[3][2] > 10 ||
//			cv.Cube_Vertex[4][0] < 0 || cv.Cube_Vertex[4][0] > width * 2 || cv.Cube_Vertex[4][1] < 0 || cv.Cube_Vertex[4][1] > height * 2 || cv.Cube_Vertex[4][2] < -10 || cv.Cube_Vertex[4][2] > 10 ||
//			cv.Cube_Vertex[5][0] < 0 || cv.Cube_Vertex[5][0] > width * 2 || cv.Cube_Vertex[5][1] < 0 || cv.Cube_Vertex[5][1] > height * 2 || cv.Cube_Vertex[5][2] < -10 || cv.Cube_Vertex[5][2] > 10 ||
//			cv.Cube_Vertex[6][0] < 0 || cv.Cube_Vertex[6][0] > width * 2 || cv.Cube_Vertex[6][1] < 0 || cv.Cube_Vertex[6][1] > height * 2 || cv.Cube_Vertex[6][2] < -10 || cv.Cube_Vertex[6][2] > 10 ||
//			cv.Cube_Vertex[7][0] < 0 || cv.Cube_Vertex[7][0] > width * 2 || cv.Cube_Vertex[7][1] < 0 || cv.Cube_Vertex[7][1] > height * 2 || cv.Cube_Vertex[7][2] < -10 || cv.Cube_Vertex[7][2] > 10)
//		{
//			continue;
//		}
//	}
//	else if (m_projection == 1)
//	{
//		if (cv.Cube_Vertex[0][2] < -10 || cv.Cube_Vertex[0][2] > 20 ||
//			cv.Cube_Vertex[1][2] < -10 || cv.Cube_Vertex[1][2] > 20 ||
//			cv.Cube_Vertex[2][2] < -10 || cv.Cube_Vertex[2][2] > 20 ||
//			cv.Cube_Vertex[3][2] < -10 || cv.Cube_Vertex[3][2] > 20 ||
//			cv.Cube_Vertex[4][2] < -10 || cv.Cube_Vertex[4][2] > 20 ||
//			cv.Cube_Vertex[5][2] < -10 || cv.Cube_Vertex[5][2] > 20 ||
//			cv.Cube_Vertex[6][2] < -10 || cv.Cube_Vertex[6][2] > 20 ||
//			cv.Cube_Vertex[7][2] < -10 || cv.Cube_Vertex[7][2] > 20)
//		{
//			continue;
//		}
//	}
//
//	if (cv.Cube_Vertex[3][2] > 1200)
//		continue;
//
//
//	if (m_drawType)
//	{
//#pragma region 큐브그리는부분(채우기)
//		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		float Crossinput1[4][1];
//		float Crossinput2[4][1];
//		float Crossinput3[4][1];
//		float Dotinput[4][1];
//		CBrush lightbrush;
//		int RGBresult = 100;
//		//할당
//		float** NormalResultmat = new float* [9];
//		for (int i = 0; i < COL; i++) {
//			NormalResultmat[i] = new float[ROW];
//		}
//
//		//원본/////////////////////////////////////////////////////////////////////////////////
//		//lightbrush.DeleteObject();
//		pDC->SelectObject(whitebrush);
//		for (int i = 0; i < 4; i++)
//		{
//			Crossinput1[i][0] = cv.Cube_Vertex[0][i];
//			Crossinput2[i][0] = cv.Cube_Vertex[1][i];
//			Crossinput3[i][0] = cv.Cube_Vertex[2][i];
//		}
//		NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
//
//		for (int i = 0; i < 4; i++)
//		{
//			Dotinput[i][0] = NormalResultmat[i][0];
//		}
//		RGBresult = matfun.Dot(Dotinput, lightpos) + 50;
//		lightbrush.CreateSolidBrush(RGB(RGBresult, RGBresult, RGBresult));
//		pDC->SelectObject(lightbrush);
//		//원본/////////////////////////////////////////////////////////////////////////////////
//		pDC->BeginPath();
//		pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//		pDC->LineTo(cv.Cube_Vertex[1][0], cv.Cube_Vertex[1][1]);
//		pDC->LineTo(cv.Cube_Vertex[2][0], cv.Cube_Vertex[2][1]);
//		pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//		pDC->EndPath();
//		pDC->StrokeAndFillPath();
//
//		///////////////////////////////////////////////////////////////////////////////////
//		lightbrush.DeleteObject();
//		pDC->SelectObject(whitebrush);
//		for (int i = 0; i < 4; i++)
//		{
//			Crossinput1[i][0] = cv.Cube_Vertex[0][i];
//			Crossinput2[i][0] = cv.Cube_Vertex[1][i];
//			Crossinput3[i][0] = cv.Cube_Vertex[5][i];
//		}
//		NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
//		for (int i = 0; i < 4; i++)
//		{
//			Dotinput[i][0] = NormalResultmat[i][0];
//		}
//		RGBresult = matfun.Dot(Dotinput, lightpos) + 50;
//		lightbrush.CreateSolidBrush(RGB(RGBresult, RGBresult, RGBresult));
//		pDC->SelectObject(lightbrush);
//		///////////////////////////////////////////////////////////////////////////////////
//
//		pDC->BeginPath();
//		pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//		pDC->LineTo(cv.Cube_Vertex[1][0], cv.Cube_Vertex[1][1]);
//		pDC->LineTo(cv.Cube_Vertex[5][0], cv.Cube_Vertex[5][1]);
//		pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//		pDC->EndPath();
//		pDC->StrokeAndFillPath();
//
//		///////////////////////////////////////////////////////////////////////////////////
//		lightbrush.DeleteObject();
//		pDC->SelectObject(whitebrush);
//		for (int i = 0; i < 4; i++)
//		{
//			Crossinput1[i][0] = cv.Cube_Vertex[0][i];
//			Crossinput2[i][0] = cv.Cube_Vertex[2][i];
//			Crossinput3[i][0] = cv.Cube_Vertex[3][i];
//		}
//		NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
//		for (int i = 0; i < 4; i++)
//		{
//			Dotinput[i][0] = NormalResultmat[i][0];
//		}
//		RGBresult = matfun.Dot(Dotinput, lightpos) + 50;
//		lightbrush.CreateSolidBrush(RGB(RGBresult, RGBresult, RGBresult));
//		pDC->SelectObject(lightbrush);
//		///////////////////////////////////////////////////////////////////////////////////
//
//		pDC->BeginPath();
//		pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//		pDC->LineTo(cv.Cube_Vertex[2][0], cv.Cube_Vertex[2][1]);
//		pDC->LineTo(cv.Cube_Vertex[3][0], cv.Cube_Vertex[3][1]);
//		pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//		pDC->EndPath();
//		pDC->StrokeAndFillPath();
//
//		///////////////////////////////////////////////////////////////////////////////////
//		lightbrush.DeleteObject();
//		pDC->SelectObject(whitebrush);
//		for (int i = 0; i < 4; i++)
//		{
//			Crossinput1[i][0] = cv.Cube_Vertex[0][i];
//			Crossinput2[i][0] = cv.Cube_Vertex[3][i];
//			Crossinput3[i][0] = cv.Cube_Vertex[7][i];
//		}
//		NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
//		for (int i = 0; i < 4; i++)
//		{
//			Dotinput[i][0] = NormalResultmat[i][0];
//		}
//		RGBresult = matfun.Dot(Dotinput, lightpos) + 50;
//		lightbrush.CreateSolidBrush(RGB(RGBresult, RGBresult, RGBresult));
//		pDC->SelectObject(lightbrush);
//		///////////////////////////////////////////////////////////////////////////////////
//
//		pDC->BeginPath();
//		pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//		pDC->LineTo(cv.Cube_Vertex[3][0], cv.Cube_Vertex[3][1]);
//		pDC->LineTo(cv.Cube_Vertex[7][0], cv.Cube_Vertex[7][1]);
//		pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//		pDC->EndPath();
//		pDC->StrokeAndFillPath();
//
//		///////////////////////////////////////////////////////////////////////////////////
//		lightbrush.DeleteObject();
//		pDC->SelectObject(whitebrush);
//		for (int i = 0; i < 4; i++)
//		{
//			Crossinput1[i][0] = cv.Cube_Vertex[0][i];
//			Crossinput2[i][0] = cv.Cube_Vertex[4][i];
//			Crossinput3[i][0] = cv.Cube_Vertex[5][i];
//		}
//		NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
//		for (int i = 0; i < 4; i++)
//		{
//			Dotinput[i][0] = NormalResultmat[i][0];
//		}
//		RGBresult = matfun.Dot(Dotinput, lightpos) + 50;
//		lightbrush.CreateSolidBrush(RGB(RGBresult, RGBresult, RGBresult));
//		pDC->SelectObject(lightbrush);
//		///////////////////////////////////////////////////////////////////////////////////
//
//		pDC->BeginPath();
//		pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//		pDC->LineTo(cv.Cube_Vertex[4][0], cv.Cube_Vertex[4][1]);
//		pDC->LineTo(cv.Cube_Vertex[5][0], cv.Cube_Vertex[5][1]);
//		pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//		pDC->EndPath();
//		pDC->StrokeAndFillPath();
//
//		///////////////////////////////////////////////////////////////////////////////////
//		lightbrush.DeleteObject();
//		pDC->SelectObject(whitebrush);
//		for (int i = 0; i < 4; i++)
//		{
//			Crossinput1[i][0] = cv.Cube_Vertex[0][i];
//			Crossinput2[i][0] = cv.Cube_Vertex[4][i];
//			Crossinput3[i][0] = cv.Cube_Vertex[7][i];
//		}
//		NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
//
//		for (int i = 0; i < 4; i++)
//		{
//			Dotinput[i][0] = NormalResultmat[i][0];
//		}
//		RGBresult = matfun.Dot(Dotinput, lightpos) + 50;
//		lightbrush.CreateSolidBrush(RGB(RGBresult, RGBresult, RGBresult));
//		pDC->SelectObject(lightbrush);
//		///////////////////////////////////////////////////////////////////////////////////
//
//		pDC->BeginPath();
//		pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//		pDC->LineTo(cv.Cube_Vertex[4][0], cv.Cube_Vertex[4][1]);
//		pDC->LineTo(cv.Cube_Vertex[7][0], cv.Cube_Vertex[7][1]);
//		pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//		pDC->EndPath();
//		pDC->StrokeAndFillPath();
//		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
//		///////////////////////////////////////////////////////////////////////////////////
//		lightbrush.DeleteObject();
//		pDC->SelectObject(whitebrush);
//		for (int i = 0; i < 4; i++)
//		{
//			Crossinput1[i][0] = cv.Cube_Vertex[6][i];
//			Crossinput2[i][0] = cv.Cube_Vertex[1][i];
//			Crossinput3[i][0] = cv.Cube_Vertex[2][i];
//		}
//		NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
//		for (int i = 0; i < 4; i++)
//		{
//			Dotinput[i][0] = NormalResultmat[i][0];
//		}
//		RGBresult = matfun.Dot(Dotinput, lightpos) + 50;
//		lightbrush.CreateSolidBrush(RGB(RGBresult, RGBresult, RGBresult));
//		pDC->SelectObject(lightbrush);
//		///////////////////////////////////////////////////////////////////////////////////
//		pDC->BeginPath();
//		pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//		pDC->LineTo(cv.Cube_Vertex[1][0], cv.Cube_Vertex[1][1]);
//		pDC->LineTo(cv.Cube_Vertex[2][0], cv.Cube_Vertex[2][1]);
//		pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//		pDC->EndPath();
//		pDC->StrokeAndFillPath();
//
//		///////////////////////////////////////////////////////////////////////////////////
//		lightbrush.DeleteObject();
//		pDC->SelectObject(whitebrush);
//		for (int i = 0; i < 4; i++)
//		{
//			Crossinput1[i][0] = cv.Cube_Vertex[6][i];
//			Crossinput2[i][0] = cv.Cube_Vertex[1][i];
//			Crossinput3[i][0] = cv.Cube_Vertex[5][i];
//		}
//		NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
//		for (int i = 0; i < 4; i++)
//		{
//			Dotinput[i][0] = NormalResultmat[i][0];
//		}
//		RGBresult = matfun.Dot(Dotinput, lightpos) + 50;
//		lightbrush.CreateSolidBrush(RGB(RGBresult, RGBresult, RGBresult));
//		pDC->SelectObject(lightbrush);
//		///////////////////////////////////////////////////////////////////////////////////
//
//		pDC->BeginPath();
//		pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//		pDC->LineTo(cv.Cube_Vertex[1][0], cv.Cube_Vertex[1][1]);
//		pDC->LineTo(cv.Cube_Vertex[5][0], cv.Cube_Vertex[5][1]);
//		pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//		pDC->EndPath();
//		pDC->StrokeAndFillPath();
//
//		///////////////////////////////////////////////////////////////////////////////////
//		lightbrush.DeleteObject();
//		pDC->SelectObject(whitebrush);
//		for (int i = 0; i < 4; i++)
//		{
//			Crossinput1[i][0] = cv.Cube_Vertex[6][i];
//			Crossinput2[i][0] = cv.Cube_Vertex[2][i];
//			Crossinput3[i][0] = cv.Cube_Vertex[3][i];
//		}
//		NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
//
//		for (int i = 0; i < 4; i++)
//		{
//			Dotinput[i][0] = NormalResultmat[i][0];
//		}
//		RGBresult = matfun.Dot(Dotinput, lightpos) + 50;
//		lightbrush.CreateSolidBrush(RGB(RGBresult, RGBresult, RGBresult));
//		pDC->SelectObject(lightbrush);
//		///////////////////////////////////////////////////////////////////////////////////
//
//		pDC->BeginPath();
//		pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//		pDC->LineTo(cv.Cube_Vertex[2][0], cv.Cube_Vertex[2][1]);
//		pDC->LineTo(cv.Cube_Vertex[3][0], cv.Cube_Vertex[3][1]);
//		pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//		pDC->EndPath();
//		pDC->StrokeAndFillPath();
//
//		///////////////////////////////////////////////////////////////////////////////////
//		lightbrush.DeleteObject();
//		pDC->SelectObject(whitebrush);
//		for (int i = 0; i < 4; i++)
//		{
//			Crossinput1[i][0] = cv.Cube_Vertex[6][i];
//			Crossinput2[i][0] = cv.Cube_Vertex[3][i];
//			Crossinput3[i][0] = cv.Cube_Vertex[7][i];
//		}
//		NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
//		for (int i = 0; i < 4; i++)
//		{
//			Dotinput[i][0] = NormalResultmat[i][0];
//		}
//		RGBresult = matfun.Dot(Dotinput, lightpos) + 50;
//		lightbrush.CreateSolidBrush(RGB(RGBresult, RGBresult, RGBresult));
//		pDC->SelectObject(lightbrush);
//		///////////////////////////////////////////////////////////////////////////////////
//
//		pDC->BeginPath();
//		pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//		pDC->LineTo(cv.Cube_Vertex[3][0], cv.Cube_Vertex[3][1]);
//		pDC->LineTo(cv.Cube_Vertex[7][0], cv.Cube_Vertex[7][1]);
//		pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//		pDC->EndPath();
//		pDC->StrokeAndFillPath();
//
//		///////////////////////////////////////////////////////////////////////////////////
//		lightbrush.DeleteObject();
//		pDC->SelectObject(whitebrush);
//		for (int i = 0; i < 4; i++)
//		{
//			Crossinput1[i][0] = cv.Cube_Vertex[6][i];
//			Crossinput2[i][0] = cv.Cube_Vertex[4][i];
//			Crossinput3[i][0] = cv.Cube_Vertex[5][i];
//		}
//		NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
//
//		for (int i = 0; i < 4; i++)
//		{
//			Dotinput[i][0] = NormalResultmat[i][0];
//		}
//		RGBresult = matfun.Dot(Dotinput, lightpos) + 50;
//		lightbrush.CreateSolidBrush(RGB(RGBresult, RGBresult, RGBresult));
//		pDC->SelectObject(lightbrush);
//		///////////////////////////////////////////////////////////////////////////////////
//
//		pDC->BeginPath();
//		pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//		pDC->LineTo(cv.Cube_Vertex[4][0], cv.Cube_Vertex[4][1]);
//		pDC->LineTo(cv.Cube_Vertex[5][0], cv.Cube_Vertex[5][1]);
//		pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//		pDC->EndPath();
//		pDC->StrokeAndFillPath();
//
//		///////////////////////////////////////////////////////////////////////////////////
//		lightbrush.DeleteObject();
//		pDC->SelectObject(whitebrush);
//		for (int i = 0; i < 4; i++)
//		{
//			Crossinput1[i][0] = cv.Cube_Vertex[6][i];
//			Crossinput2[i][0] = cv.Cube_Vertex[4][i];
//			Crossinput3[i][0] = cv.Cube_Vertex[7][i];
//		}
//		NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
//		for (int i = 0; i < 4; i++)
//		{
//			Dotinput[i][0] = NormalResultmat[i][0];
//		}
//		RGBresult = matfun.Dot(Dotinput, lightpos) + 50;
//		lightbrush.CreateSolidBrush(RGB(RGBresult, RGBresult, RGBresult));
//		pDC->SelectObject(lightbrush);
//		///////////////////////////////////////////////////////////////////////////////////
//
//		pDC->BeginPath();
//		pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//		pDC->LineTo(cv.Cube_Vertex[4][0], cv.Cube_Vertex[4][1]);
//		pDC->LineTo(cv.Cube_Vertex[7][0], cv.Cube_Vertex[7][1]);
//		pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//		pDC->EndPath();
//		pDC->StrokeAndFillPath();
//#pragma endregion
//	}
//	else
//	{
//#pragma region 큐브그리는부분
//		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//		pDC->LineTo(cv.Cube_Vertex[1][0], cv.Cube_Vertex[1][1]);
//		pDC->LineTo(cv.Cube_Vertex[2][0], cv.Cube_Vertex[2][1]);
//		pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//
//		pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//		pDC->LineTo(cv.Cube_Vertex[1][0], cv.Cube_Vertex[1][1]);
//		pDC->LineTo(cv.Cube_Vertex[5][0], cv.Cube_Vertex[5][1]);
//		pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//
//		pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//		pDC->LineTo(cv.Cube_Vertex[2][0], cv.Cube_Vertex[2][1]);
//		pDC->LineTo(cv.Cube_Vertex[3][0], cv.Cube_Vertex[3][1]);
//		pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//
//		pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//		pDC->LineTo(cv.Cube_Vertex[3][0], cv.Cube_Vertex[3][1]);
//		pDC->LineTo(cv.Cube_Vertex[7][0], cv.Cube_Vertex[7][1]);
//		pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//
//		pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//		pDC->LineTo(cv.Cube_Vertex[4][0], cv.Cube_Vertex[4][1]);
//		pDC->LineTo(cv.Cube_Vertex[5][0], cv.Cube_Vertex[5][1]);
//		pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//
//		pDC->LineTo(cv.Cube_Vertex[4][0], cv.Cube_Vertex[4][1]);
//		pDC->LineTo(cv.Cube_Vertex[7][0], cv.Cube_Vertex[7][1]);
//		pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
//		pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//		pDC->LineTo(cv.Cube_Vertex[1][0], cv.Cube_Vertex[1][1]);
//		pDC->LineTo(cv.Cube_Vertex[2][0], cv.Cube_Vertex[2][1]);
//		pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//
//		pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//		pDC->LineTo(cv.Cube_Vertex[1][0], cv.Cube_Vertex[1][1]);
//		pDC->LineTo(cv.Cube_Vertex[5][0], cv.Cube_Vertex[5][1]);
//		pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//
//		pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//		pDC->LineTo(cv.Cube_Vertex[2][0], cv.Cube_Vertex[2][1]);
//		pDC->LineTo(cv.Cube_Vertex[3][0], cv.Cube_Vertex[3][1]);
//		pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//
//		pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//		pDC->LineTo(cv.Cube_Vertex[3][0], cv.Cube_Vertex[3][1]);
//		pDC->LineTo(cv.Cube_Vertex[7][0], cv.Cube_Vertex[7][1]);
//		pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//
//		pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//		pDC->LineTo(cv.Cube_Vertex[4][0], cv.Cube_Vertex[4][1]);
//		pDC->LineTo(cv.Cube_Vertex[5][0], cv.Cube_Vertex[5][1]);
//		pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//
//		pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//		pDC->LineTo(cv.Cube_Vertex[4][0], cv.Cube_Vertex[4][1]);
//		pDC->LineTo(cv.Cube_Vertex[7][0], cv.Cube_Vertex[7][1]);
//		pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//#pragma endregion
//
//	}
//	//m_CubeSize = 100;
//	//m_SphereRadius = 200;
//	//m_TorusRadius = 200;
//	//m_nCircleRadius = 70;
//
//	//rxvalue = 0;
//	//ryvalue = 0;
//	//rzvalue = 0;
//
//	//Figure_xMove = 0;
//	//Figure_yMove = 0;		
//
//}//end for(auto cv : m_vCube)