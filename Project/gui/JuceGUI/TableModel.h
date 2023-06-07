#pragma once
#include <JuceHeader.h>
#include "NamedVector3.h"
class TableModel final : public juce::TableListBoxModel
{
public:
	TableModel() = default;

	int getNumRows() override;
	void paintRowBackground(Graphics&, int rowNumber, int width, int height, bool rowIsSelected) override;
	void paintCell(Graphics&,
		int 	rowNumber,
		int 	columnId,
		int 	width,
		int 	height,
		bool 	rowIsSelected
	)override;

	void AddNamedVectorData(const NamedVector3& vector)
	{
		m_Vectors.push_back(vector);
	}
	void Clear() { m_Vectors.clear(); }

private:
	std::vector<NamedVector3> m_Vectors;
};
