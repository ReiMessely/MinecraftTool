#pragma once
#include <JuceHeader.h>
#include "NamedVector3.h"
class TableModel :public juce::TableListBoxModel
{
public:
	TableModel();

	int getNumRows() override;
	void paintRowBackground(Graphics&, int rowNumber, int width, int height, bool rowIsSelected) override;
	void paintCell(Graphics&,
		int 	rowNumber,
		int 	columnId,
		int 	width,
		int 	height,
		bool 	rowIsSelected
	)override;

private:
	std::vector<NamedVector3> m_Vectors;
};
