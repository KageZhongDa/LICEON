import React, { useState, useEffect } from 'react';
import ReactDOM from 'react-dom/client';
import {
	ChakraProvider,
	Center,
	Text,
	HStack,
	VStack,
	Heading,
	Box,
	Flex,
	Spacer,
} from '@chakra-ui/react';
import { Card, CardHeader, CardBody } from '@chakra-ui/react';
import { Droplet, Filter, Thermometer } from 'react-feather';

import {
	Table,
	Thead,
	Tbody,
	Tfoot,
	Tr,
	Th,
	Td,
	TableCaption,
	TableContainer,
} from '@chakra-ui/react';

import { IP_KAGE_SERVER, IP_ESP32_LICEON, SSID_ESP32_LICEON } from '../env.js';

function InfoCard({ header, Icon, value, value2, read }) {
	return (
		<Card py={5} px={5} flex={1}>
			<CardHeader>
				<Center>
					<Heading size={'sm'}>{header}</Heading>
				</Center>
			</CardHeader>
			<CardBody>
				<HStack spacing={4} justifyContent={'space-around'}>
					<VStack spacing={2} alignItems={'flex-start'}>
						<Text fontSize={12} fontWeight={'bold'}>
							Value:
						</Text>
						<Text fontSize={12} fontWeight={'bold'}>
							Reading:
						</Text>
					</VStack>
					<VStack spacing={2} alignItems={'flex-start'}>
						<Text fontSize={12}>{value2 != null ? value + ' ' + value2 : value}</Text>
						<Text fontSize={12}>{read}</Text>
					</VStack>
					<Box>
						<Icon size={50} color={'#82ccdd'} />
					</Box>
				</HStack>
			</CardBody>
		</Card>
	);
}

function InfoSection({ data }) {
	const [latestData, setLatestData] = useState('');
	const [acdRead, setAcdRead] = useState('');
	const [trbRead, setTrbRead] = useState('');
	const [tmpRead, setTmpRead] = useState('');

	useEffect(() => {
		if (data.length > 0) {
			// Access data[0].acdval or perform other operations
			setLatestData(data[0]);

			if (data[0].acdval <= 2) {
				setAcdRead('Very Acidic');
			} else if (data[0].acdval <= 3) {
				setAcdRead('Moderately Acidic');
			} else if (data[0].acdval <= 4) {
				setAcdRead('Moderately Acidic');
			} else if (data[0].acdval <= 5) {
				setAcdRead('Slightly Acidic');
			} else if (data[0].acdval <= 6) {
				setAcdRead('Slightly Acidic');
			} else if (data[0].acdval <= 7) {
				setAcdRead('Neutral');
			} else if (data[0].acdval <= 8) {
				setAcdRead('Neutral');
			} else if (data[0].acdval <= 9) {
				setAcdRead('Slightly Alkaline');
			} else if (data[0].acdval <= 10) {
				setAcdRead('Moderately Alkaline');
			} else if (data[0].acdval <= 11) {
                                setAcdRead('Moderately Alkaline');
			} else if (data[0].acdval <= 12) {
                                setAcdRead('Very Alkaline');
			} else if (data[0].acdval < 13) {
                                setAcdRead('Very Alkaline');
			} else if (data[0].acdval >= 13) {
                                setAcdRead('Very Alkaline');
			}

			if (data[0].trbval >= 1000) {
				setTrbRead('Densely Cloudy');
			} else if (data[0].trbval >= 500) {
				setTrbRead('Cloudy');
			} else if (data[0].trbval >= 200) {
				setTrbRead('Slightly Cloudy');
			} else if (data[0].trbval >= 100) {
				setTrbRead('Blurry');
			} else if (data[0].trbval >= 50) {
				setTrbRead('Slightly Blurry');
			} else if (data[0].trbval >= 20) {
				setTrbRead('Clear');
			} else if (data[0].trbval >= 0) {
				setTrbRead('Crystal Clear');
			}

			if (data[0].tmpcelval >= 100) {
				setTmpRead('Above Boiling');
			} else if (data[0].tmpcelval >= 70) {
				setTmpRead('Extremely Hot');
			} else if (data[0].tmpcelval >= 50) {
				setTmpRead('Very Hot');
			} else if (data[0].tmpcelval >= 40) {
				setTmpRead('Hot');
			} else if (data[0].tmpcelval >= 30) {
				setTmpRead('Warm');
			} else if (data[0].tmpcelval >= 25) {
				setTmpRead('Cold');
			} else if (data[0].tmpcelval >= 18) {
				setTmpRead('Very Cold');
			} else if (data[0].tmpcelval >= 12) {
				setTmpRead('Ice Cold');     
			}
		}
	}, [data]);

	return (
		<Flex
			justifyContent={{ base: 'center', lg: 'space-around' }}
			flexDirection={{ base: 'column', lg: 'row' }}>
			<InfoCard
				header={'Acidity'}
				Icon={Droplet}
				value={latestData !== '' ? String(latestData.acdval.toFixed(2)) + ' pH' : ''}
				read={acdRead}
			/>
			<Spacer maxW={2} />
			<InfoCard
				header={'Turbidity'}
				Icon={Filter}
				value={latestData !== '' ? String(latestData.trbval.toFixed(2)) + ' Nt' : ''}
				read={trbRead}
			/>
			<Spacer maxW={2} />
			<InfoCard
				header={'Temperature'}
				Icon={Thermometer}
				value={latestData !== '' ? latestData.tmpcelval.toFixed(2) + '^C' : ''}
				value2={latestData !== '' ? latestData.tmpfarval.toFixed(2) + '^F' : ''}
				read={tmpRead}
			/>
		</Flex>
	);
}

function TableCard({ data }) {
	return (
		<TableContainer flex={1}>
			<Table size={'sm'}>
				<Thead>
					<Tr>
						<Th fontSize={10}>Datetime</Th>
						<Th fontSize={10}>AcdVal</Th>
						{/* <Th fontSize={10}>AcdRead</Th> */}
						<Th fontSize={10}>TrbVal</Th>
						{/* <Th fontSize={10}>TrbRead</Th> */}
						<Th fontSize={10}>TmpCelVal</Th>
						<Th fontSize={10}>TmpFarVal</Th>
						{/* <Th fontSize={10}>TmpRead</Th> */}
					</Tr>
				</Thead>
				<Tbody>
					{data.map(record => (
						<Tr key={record.id}>
							<Td fontSize={12}>{record.id}</Td>
							<Td fontSize={12}>{record.acdval}</Td>
							<Td fontSize={12}>{record.trbval}</Td>
							<Td fontSize={12}>{record.tmpcelval}</Td>
							<Td fontSize={12}>{record.tmpfarval}</Td>
						</Tr>
					))}
				</Tbody>
			</Table>
		</TableContainer>
	);
}

function App() {
	const [records, setRecords] = useState([]);

	useEffect(() => {
		console.log(IP_KAGE_SERVER);

		const eventSource = new EventSource(`http://${IP_KAGE_SERVER}:5000/api/realtime-data`);

		eventSource.onmessage = event => {
			let newRecords = JSON.parse(event.data);
			// Sorting the array by timestamp in descending order
			newRecords.sort((a, b) => new Date(b.id) - new Date(a.id));
			setRecords(newRecords);
		};

		return () => {
			eventSource.close();
		};
	}, []);

	return (
		<Center>
			<VStack py={30} h={'100vh'} w={'80%'} align={'stretch'} spacing={8}>
				<Card>
					<HStack
						justifyContent={'space-between'}
						flexDirection={{ base: 'column', lg: 'row' }}
						p={8}>
						<Box>
							<Text fontSize={12}>
								<b>IP ADDRESS:</b> {IP_ESP32_LICEON}
							</Text>
							<Text fontSize={12}>
								<b>SSID:</b> {SSID_ESP32_LICEON}
							</Text>
						</Box>
						<Box>
							<Text fontSize={12} fontWeight={'semibold'}>
								Comparison Of Water Quality Between Tap And Rainwater Using Arduino Water
								Sensor.
							</Text>
						</Box>
					</HStack>
				</Card>
				<InfoSection data={records} />
				<HStack justifyContent={'space-between'}>
					<TableCard data={records} />
				</HStack>
			</VStack>
		</Center>
	);
}

function Root() {
	return (
		<ChakraProvider>
			<App />
		</ChakraProvider>
	);
}

ReactDOM.createRoot(document.getElementById('root')).render(<Root />);
