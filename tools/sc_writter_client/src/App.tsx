import { FC, useState } from 'react';

import { ScClientHandler } from './utils/sc-client-handler.class';
import Header from './components/header/Header';
import LeftPanel from './components/left-panel/LeftPanel';
import RightPanel from './components/right-panel/RightPanel';

import './App.css';
import './App.css';

const App: FC = () => {
  const [connect, setConnect] = useState(true);
  // const [constructions, setConstructions] = useState(new Array<{ name: string; text: string }>());
  const [constructions, setConstructions] = useState([{ name: 'New construction 1', text: '' }]);
  const [selectedConstruction, setSelectedConstruction] = useState(constructions[0]);
  const [selectedIndex, setSelectedIndex] = useState(0);

  const scClient = new ScClientHandler('ws://localhost:8090');

  const handleUpload = async (i: number) => {
   await scClient.uploadScElementsBySCs([constructions[i].text]);
  }

  const updateConnectionStatus = () => {
    console.log(scClient.getIsConnected());

    setConnect(scClient.getIsConnected());
  }

  const addConstruction = (name: string) => {
    setConstructions((oldState) => {
      return [...oldState, { name, text: '' }];
    });
  }

  const setConstruction = (i: number) => {
    setSelectedIndex(i);
    setSelectedConstruction(constructions[i]);
  }

  const onChangeName = (name: string, i: number) => {
    setConstructions((old) => {
      old[i].name = name;

      return [...old];
    });
  }

  const onChangeText = (text: string, i: number) => {
    setConstructions((old) => {
      old[i].text = text;

      return [...old];
    });
  }

  return (
    <div className="App">
      <Header />
      <main>
        <LeftPanel
          isConnected={connect}
          updateConnectHandler={updateConnectionStatus}
          constructions={constructions}
          setConstructions={addConstruction}
          setConstruction={setConstruction}
        />
        <RightPanel 
          selectedConstruction={selectedConstruction}
          index={selectedIndex}
          onChangeName={onChangeName}
          onChangeText={onChangeText}
          handleUpload={handleUpload}
        />
      </main>
    </div>
  );
}

export default App;
