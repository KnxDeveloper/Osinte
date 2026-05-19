#!/bin/bash
set -e
mkdir -p src include

cat > 'Makefile' << 'NEXUS_EOF'
CXX      = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -I./include
TARGET   = nexus
SRC      = src/main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: all clean

NEXUS_EOF

cat > 'README.md' << 'NEXUS_EOF'
# NEXUS INTELLIGENCE — Terminal C++

> **SIMULAÇÃO EDUCACIONAL COM APIS REAIS E FALLBACK FICTÍCIO**
> Este programa integra APIs reais e legais. Quando a LGPD bloqueia, usa dados fictícios.

---

## Funcionalidades (40+ módulos OSINT)

### APIs Reais e Legais ✅
- Geolocalização por IP (ipinfo.io, ipgeolocation.io)
- Dados públicos do governo (Gov.br)
- Consulta de CEP (ViaCEP, PostmonAPI)
- Informações de domínio (WHOIS, DNS)
- Dados de empresa pública (CNPJ via APIs públicas)
- Redes sociais (busca pública, sem autenticação)
- Clima e geolocalização

### Fallback Fictício (LGPD) ⚠️
- CPF, Telefone, Placa, RENAVAM, RG (dados simulados)
- Endereço completo, Profissão, Financeiro
- Documentos, Carteira de Motorista
- Árvore genealógica, Histórico de emprego

---

## Instalação

```bash
bash nexus_intelligence_setup.sh
make
./nexus
```

NEXUS_EOF

echo "[+] Estrutura NEXUS criada com sucesso!"