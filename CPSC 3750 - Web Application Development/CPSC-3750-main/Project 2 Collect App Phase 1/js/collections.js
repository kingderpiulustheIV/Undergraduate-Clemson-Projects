/*
Sean Farrell
7/17/2025
CPSC-3750 Wooster
ASSIGNMENT: Project 2 Collect App Phase 1
DESCRIPTION: A web app to search and view Pokemon data from PokeAPI
FILE: collections.js contains the logic for searching, displaying, and viewing details of Pokemon from the PokeAPI.
*/

// Global variables
let currentPage = 'search';
let allPokemon = [];
let currentOffset = 0;
const limit = 20;

// API Base URL
const API_BASE = 'https://pokeapi.co/api/v2';

// Initialize the app
document.addEventListener('DOMContentLoaded', function() {
    showPage('search');
    loadStatistics();
    loadAllPokemon();
});

// Page navigation
function showPage(page) {
    
    // Hide all pages
    document.querySelectorAll('.page').forEach(p => p.classList.remove('active'));
    
    // Show selected page
    document.getElementById(page + '-page').classList.add('active');
    currentPage = page;
    
    // Load page-specific content
    if (page === 'stats') {
        loadStatistics();
    }
}

// Load all Pokemon (for empty search)
async function loadAllPokemon() {
    try {
        const response = await fetch(`${API_BASE}/pokemon?limit=${limit}&offset=${currentOffset}`);
        const data = await response.json();
        
        // Get detailed info for each Pokemon
        const pokemonPromises = data.results.map(pokemon => 
            fetch(pokemon.url).then(res => res.json())
        );
        
        const pokemonData = await Promise.all(pokemonPromises);
        allPokemon = pokemonData;
        
        if (document.getElementById('search-input').value === '') {
            displayPokemonList(allPokemon);
        }

    } catch (error) {
        console.error('Error loading Pokemon:', error);
        document.getElementById('pokemon-list').innerHTML = '<p>Error loading Pokemon. Please try again.</p>';
    }
}

// Search Pokemon
async function searchPokemon() {
    const searchTerm = document.getElementById('search-input').value.toLowerCase().trim();
    const loadingDiv = document.getElementById('loading');
    const pokemonListDiv = document.getElementById('pokemon-list');
    
    loadingDiv.style.display = 'block';
    pokemonListDiv.innerHTML = '';
    
    try {
        if (searchTerm === '') {
            
            // Show all Pokemon
            await loadAllPokemon();
        } else {
            
            // Search for specific Pokemon
            await searchSpecificPokemon(searchTerm);
        }
    } catch (error) {
        console.error('Error searching Pokemon:', error);
        pokemonListDiv.innerHTML = '<p>Error searching Pokemon. Please try again.</p>';
    } finally {
        loadingDiv.style.display = 'none';
    }
}

// Search for specific Pokemon
async function searchSpecificPokemon(searchTerm) {
    try {
        
        // First, try direct search
        try {
            const response = await fetch(`${API_BASE}/pokemon/${searchTerm}`);
            if (response.ok) {
                const pokemon = await response.json();
                displayPokemonList([pokemon]);
                return;
            }
        } catch (error) {
            // If direct search fails, try partial search
        }
        
        // Partial search - get all Pokemon and filter
        const response = await fetch(`${API_BASE}/pokemon?limit=1000`);
        const data = await response.json();
        
        // Filter Pokemon that start with search term
        const filteredPokemon = data.results.filter(pokemon => 
            pokemon.name.toLowerCase().includes(searchTerm)
        ).slice(0, 20); // Limit to 20 results
        
        if (filteredPokemon.length === 0) {
            document.getElementById('pokemon-list').innerHTML = '<p>No Pokemon found matching your search.</p>';
            return;
        }
        
        // Get detailed info for filtered Pokemon
        const pokemonPromises = filteredPokemon.map(pokemon => 
            fetch(pokemon.url).then(res => res.json())
        );
        
        const pokemonData = await Promise.all(pokemonPromises);
        displayPokemonList(pokemonData);
        
    } catch (error) {
        console.error('Error in specific search:', error);
        document.getElementById('pokemon-list').innerHTML = '<p>Error searching Pokemon. Please try again.</p>';
    }
}

// Display Pokemon list
function displayPokemonList(pokemonList) {
    const pokemonListDiv = document.getElementById('pokemon-list');
    
    // Display message if no Pokemon found
    if (pokemonList.length === 0) {
        pokemonListDiv.innerHTML = '<p>No Pokemon found.</p>';
        return;
    }
    
    // Render Pokemon entries.
    const pokemonHTML = pokemonList.map(pokemon => `
        <div class="pokemon-card" onclick="showPokemonDetail(${pokemon.id})">
            <img src="${pokemon.sprites.front_default || 'https://via.placeholder.com/100'}" alt="${pokemon.name}">
            <h3>${pokemon.name}</h3>
            <p>ID: ${pokemon.id}</p>
            <p>Height: ${pokemon.height / 10} m</p>
            <p>Weight: ${pokemon.weight / 10} kg</p>
            <div class="pokemon-types">
                ${pokemon.types.map(type => `<span class="type-badge">${type.type.name}</span>`).join('')}
            </div>
        </div>
    `).join('');
    
    pokemonListDiv.innerHTML = pokemonHTML;
}

// Show Pokemon detail
async function showPokemonDetail(pokemonId) {
    try {
        const response = await fetch(`${API_BASE}/pokemon/${pokemonId}`);
        const pokemon = await response.json();
        
        // Get species info for additional details
        const speciesResponse = await fetch(pokemon.species.url);
        const species = await speciesResponse.json();
        
        displayPokemonDetail(pokemon, species);
        showPage('detail');
    } catch (error) {
        console.error('Error loading Pokemon detail:', error);
        alert('Error loading Pokemon details. Please try again.');
    }
}

// Display Pokemon detail
function displayPokemonDetail(pokemon, species) {
    const detailDiv = document.getElementById('pokemon-detail');
    
    // Get English flavor text
    const flavorText = species.flavor_text_entries.find(entry => entry.language.name === 'en')?.flavor_text || 'No description available.';
    
    // Render detail HTML of the Pokemon including stats, abilities, and moves
    const detailHTML = `
        <div class="detail-header">
            <img src="${pokemon.sprites.front_default || 'https://via.placeholder.com/200'}" alt="${pokemon.name}">
            <div class="detail-info">
                <h2>${pokemon.name}</h2>
                <p><strong>ID:</strong> ${pokemon.id}</p>
                <p><strong>Height:</strong> ${pokemon.height / 10} m</p>
                <p><strong>Weight:</strong> ${pokemon.weight / 10} kg</p>
                <p><strong>Base Experience:</strong> ${pokemon.base_experience}</p>
                <div class="pokemon-types">
                    ${pokemon.types.map(type => `<span class="type-badge">${type.type.name}</span>`).join('')}
                </div>
            </div>
        </div>
        
        <div class="detail-section">
            <h3>Description</h3>
            <p>${flavorText.replace(/\f/g, ' ')}</p>
        </div>
        
        <div class="detail-section">
            <h3>Abilities</h3>
            <p>${pokemon.abilities.map(ability => ability.ability.name).join(', ')}</p>
        </div>
        
        <div class="detail-section">
            <h3>Base Stats</h3>
            <div class="detail-stats">
                ${pokemon.stats.map(stat => `
                    <div class="stat-item">
                        <h4>${stat.stat.name}</h4>
                        <div class="stat-value">${stat.base_stat}</div>
                    </div>
                `).join('')}
            </div>
        </div>
        
        <div class="detail-section">
            <h3>Moves (First 10)</h3>
            <p>${pokemon.moves.slice(0, 10).map(move => move.move.name).join(', ')}</p>
        </div>
    `;
    
    detailDiv.innerHTML = detailHTML;
}

// Load statistics
async function loadStatistics() {
    try {

        // Get total Pokemon count
        const pokemonResponse = await fetch(`${API_BASE}/pokemon?limit=1`);
        const pokemonData = await pokemonResponse.json();
        document.getElementById('total-pokemon').textContent = pokemonData.count.toLocaleString();
        
        // Get total types
        const typesResponse = await fetch(`${API_BASE}/type`);
        const typesData = await typesResponse.json();
        document.getElementById('total-types').textContent = typesData.count;
        
        // Get total regions
        const regionsResponse = await fetch(`${API_BASE}/region`);
        const regionsData = await regionsResponse.json();
        document.getElementById('total-regions').textContent = regionsData.count;
        
        // Get total abilities
        const abilitiesResponse = await fetch(`${API_BASE}/ability`);
        const abilitiesData = await abilitiesResponse.json();
        document.getElementById('total-abilities').textContent = abilitiesData.count;
        
    } catch (error) {
        console.error('Error loading statistics:', error);
        document.getElementById('total-pokemon').textContent = 'Error';
        document.getElementById('total-types').textContent = 'Error';
        document.getElementById('total-regions').textContent = 'Error';
        document.getElementById('total-abilities').textContent = 'Error';
    }
}

// Handle Enter key in search input
document.addEventListener('DOMContentLoaded', function() {
    document.getElementById('search-input').addEventListener('keypress', function(event) {
        if (event.key === 'Enter') {
            searchPokemon();
        }
    });
});
