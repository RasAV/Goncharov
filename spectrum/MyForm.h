#pragma once

namespace spectrum {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Xml;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected:
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox3;

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(93, 153);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(125, 35);
			this->button1->TabIndex = 0;
			this->button1->Text = L"select file";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(93, 194);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(264, 273);
			this->textBox1->TabIndex = 1;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox1_TextChanged);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(520, 455);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(44, 25);
			this->button2->TabIndex = 2;
			this->button2->Text = L"test";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(93, 39);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 22);
			this->textBox2->TabIndex = 3;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(90, 19);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(86, 17);
			this->label1->TabIndex = 4;
			this->label1->Text = L"min Intensity";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(90, 87);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(89, 17);
			this->label2->TabIndex = 5;
			this->label2->Text = L"max Intensity";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(93, 108);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(100, 22);
			this->textBox3->TabIndex = 6;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(576, 492);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			String^ fileName = openFileDialog1->FileName;

			XmlTextReader reader(fileName);

			String^ stringMin = textBox2->Text;
			String^ stringMax = textBox3->Text;
			int min = Convert::ToInt32(stringMin);
			int max = Convert::ToInt32(stringMax);

			//Дойдем до тэга <Spectrum>
			while (reader.ReadToFollowing("Spectrum"))
			{
				textBox1->Text += "Файл" + fileName + "> \r\n" + "\r\n";

				textBox1->Text += "Пиксель" + "  ||   " + "Интенсивность" + "\r\n";

				int pixelCount = 0;//Вдруг нам будет нужен счетчик точек. Например, для массива

				//Теперь в тэге <Spectrum> найдем все точки в виде тэгов <Pixel>
				if (reader.ReadToDescendant("Pixel"))
				{
					//Все тэги <Pixel> находим в цикле
					do
					{
						pixelCount++;//Увеличиваем счетчик числа найденных точек

						int index, intensity;
						String^ Type;

						//Считываем атрибут
						Type = reader.GetAttribute("type");



						//Внутри пикселя есть тэги <index> и <intensity>.
						//Вытащим все тэги в отдельное дерево
						XmlReader^ inner = reader.ReadSubtree();

						//И пробежимся по всем внутренностям данного поддерева точки
						while (inner->Read())
						{
							//Если текущий элемент это открывающий тэг <index>,
							//то следующий элемент - это текст внутри тэга <index></index>
							if ((inner->Name == "Index") && (inner->NodeType == XmlNodeType::Element))
							{
								//Поэтому считываем еще один элемент и этот элемент то, что нам нужно
								inner->Read();
								index = Convert::ToInt32(inner->Value);
							}
							//Если текущий элемент это открывающий тэг <Intensity>,
							//то следующий элемент - это текст внутри тэга <Intensity></Intensity>
							if ((inner->Name == "Intensity") && (inner->NodeType == XmlNodeType::Element))
							{
								//Поэтому считываем еще один элемент и этот элемент то, что нам нужно
								inner->Read();
								intensity = Convert::ToInt32(inner->Value);
							}
						}

						//Выведем считанную информацию 
						//textBox1->Text += "Пиксель №" + pixelCount.ToString() + "  ||  ";
						if ( (intensity >= min) && (intensity <= max) )
						{
							textBox1->Text += index.ToString() + "        " + intensity.ToString() + "\r\n";
						}

					} while (reader.ReadToNextSibling("Pixel"));
				}
			}
		}
	}
	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			String^ fileName = openFileDialog1->FileName;

			XmlTextReader reader(fileName);
			
			String^ str;
			StreamReader^ din = File::OpenText(fileName);
			int number_of_lines = 0;
			while ((str = din->ReadLine()) != nullptr)//Считываем строчку из файла в str
			{
				number_of_lines++;
			}

			//textBox1->Text += number_of_lines + "\r\n";

			for (int i = 0; i < number_of_lines-1; i++)
			{

			}


			while (reader.Read())
			{
				switch (reader.NodeType)
				{
				case XmlNodeType::Text: //Display the text in each element.
					textBox1->Text += "" + reader.Value + "\r\n";
					break;
				}
			}
		}
	}
};
}
