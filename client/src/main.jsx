import React from 'react';
import ReactDOM from 'react-dom/client';
import { ChakraProvider, Center, Text, HStack, VStack, Heading, Box } from '@chakra-ui/react';
import { Card, CardHeader, CardBody, CardFooter } from '@chakra-ui/react';
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

function InfoCard({ header, Icon }) {
	return (
		<Card flex={1} py={25} px={5}>
			<CardHeader>
				<Center>
					<Heading size={'sm'}>{header}</Heading>
				</Center>
			</CardHeader>
			<CardBody>
				<HStack spacing={4} justifyContent={'space-between'}>
					<Box>
						<Text fontSize={12} fontWeight={'bold'}>
							Voltage:
						</Text>
						<Text fontSize={12} fontWeight={'bold'}>
							Value:
						</Text>
						<Text fontSize={12} fontWeight={'bold'}>
							Reading:
						</Text>
					</Box>
					<Box>
						<Text fontSize={12}>3.45</Text>
						<Text fontSize={12}>2.54 pH</Text>
						<Text fontSize={12}>Slightly Cloudy</Text>
					</Box>
					<Box>
						<Icon size={70} color={'#82ccdd'} />
					</Box>
				</HStack>
			</CardBody>
		</Card>
	);
}

function InfoSection() {
	return (
		<HStack justifyContent={'space-between'}>
			<InfoCard header={'Acidity'} Icon={Droplet} />
			<InfoCard header={'Turbidity'} Icon={Filter} />
			<InfoCard header={'Temperature'} Icon={Thermometer} />
		</HStack>
	);
}

function TableCard() {
	return (
		<TableContainer flex={1}>
			<Table size={'sm'}>
				<Thead>
					<Tr>
						<Th fontSize={10}>Datetime</Th>
						<Th fontSize={10}>AcVolt</Th>
						<Th fontSize={10}>AcVal</Th>
						<Th fontSize={10}>AcRead</Th>
						<Th fontSize={10}>TrVolt</Th>
						<Th fontSize={10}>TrVal</Th>
						<Th fontSize={10}>TrRead</Th>
						<Th fontSize={10}>TmVolt</Th>
						<Th fontSize={10}>TmVal</Th>
						<Th fontSize={10}>TmRead</Th>
					</Tr>
				</Thead>
				<Tbody>
					<Tr>
						<Td fontSize={12}>2022-02-06 15:30</Td>
						<Td fontSize={12}>5</Td>
						<Td fontSize={12}>23</Td>
						<Td fontSize={12}>Cloudy</Td>
						<Td fontSize={12}>5</Td>
						<Td fontSize={12}>23</Td>
						<Td fontSize={12}>Cloudy</Td>
						<Td fontSize={12}>5</Td>
						<Td fontSize={12}>23</Td>
						<Td fontSize={12}>Cloudy</Td>
					</Tr>
					<Tr>
						<Td fontSize={12}>2022-02-06 15:30</Td>
						<Td fontSize={12}>5</Td>
						<Td fontSize={12}>23</Td>
						<Td fontSize={12}>Cloudy</Td>
						<Td fontSize={12}>5</Td>
						<Td fontSize={12}>23</Td>
						<Td fontSize={12}>Cloudy</Td>
						<Td fontSize={12}>5</Td>
						<Td fontSize={12}>23</Td>
						<Td fontSize={12}>Cloudy</Td>
					</Tr>
					<Tr>
						<Td fontSize={12}>2022-02-06 15:30</Td>
						<Td fontSize={12}>5</Td>
						<Td fontSize={12}>23</Td>
						<Td fontSize={12}>Cloudy</Td>
						<Td fontSize={12}>5</Td>
						<Td fontSize={12}>23</Td>
						<Td fontSize={12}>Cloudy</Td>
						<Td fontSize={12}>5</Td>
						<Td fontSize={12}>23</Td>
						<Td fontSize={12}>Cloudy</Td>
					</Tr>
				</Tbody>
			</Table>
		</TableContainer>
	);
}

function App() {
	return (
		<Center>
			<VStack py={30} h={'100vh'} align={'stretch'} spacing={8}>
				<Card>
					<HStack justifyContent={'space-between'} p={8}>
						<Box>
							<Text fontSize={14}>
								<b>IP ADDRESS:</b> 192.168.1.13
							</Text>
							<Text fontSize={14}>
								<b>SSID:</b> ESP32-NETWORK
							</Text>
						</Box>
						<Box>
							<Text fontSize={14} fontWeight={'semibold'}>
								Comparison Of Water Quality Between Tap And Rainwater Using Arduino Water
								Sensor.
							</Text>
						</Box>
					</HStack>
				</Card>
				<InfoSection />
				<HStack justifyContent={'space-between'}>
					<TableCard />
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
