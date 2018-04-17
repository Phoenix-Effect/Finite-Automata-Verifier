var nodes = [
	{id: 595, label: '1SP#', color: '#FF7F32'},
	{id: 7654, label: 'Dead-StateSP#', color: {background:'#78BE20', border:'green'}},
	{id: 893, label: '12SP#', color: '#5C6670'},
	{id: 596, label: '2SP#', color: '#5C6670'},
	{id: 1244, label: '123SP#', color: '#5C6670'},
	{id: 597, label: '3SP#', color: {background:'#78BE20', border:'green'}},
	{id: 896, label: '23SP#', color: '#5C6670'}
];

var edges = [
	{from: 595, to:7654, arrows:'to', label: 'a', font: {align: 'top'}},
	{from: 595, to:893, arrows:'to', label: 'b', font: {align: 'top'}},
	{from: 7654, to:7654, arrows:'to', label: 'a, b', font: {align: 'top'}},
	{from: 893, to:596, arrows:'to', label: 'a', font: {align: 'top'}},
	{from: 893, to:1244, arrows:'to', label: 'b', font: {align: 'top'}},
	{from: 596, to:596, arrows:'to', label: 'a', font: {align: 'top'}},
	{from: 596, to:597, arrows:'to', label: 'b', font: {align: 'top'}},
	{from: 1244, to:896, arrows:'to', label: 'a', font: {align: 'top'}},
	{from: 1244, to:1244, arrows:'to', label: 'b', font: {align: 'top'}},
	{from: 597, to:597, arrows:'to', label: 'a, b', font: {align: 'top'}},
	{from: 896, to:896, arrows:'to', label: 'a', font: {align: 'top'}},
	{from: 896, to:597, arrows:'to', label: 'b', font: {align: 'top'}}
];