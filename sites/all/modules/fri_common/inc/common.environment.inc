<?php

  // Settings for the site that are dependent on the server
  $server_name = $_SERVER['SERVER_NAME'];
  $server_name = strtolower( trim( $server_name ) );
  switch( $server_name ) :
    case 'd2dtest.acuitys.com':
      // Microstrategy
      define( 'ENV_MSTR_USERNAME', 'd2d-portal-user' );
      define( 'ENV_MSTR_PASSWORD', '34A!dn@5hd' );

      // Tableau
      define( 'ENV_TABLEAU_TICKET_HOST', 'https://staging-tableau.d2d.gsa.gov/trusted/' );
      define( 'ENV_TABLEAU_CONTENT_HOST', 'https://staging-tableau.d2d.gsa.gov/trusted/' );
    break;

    case 'staging.d2d.gsa.gov':
      // Microstrategy
      define( 'ENV_MSTR_USERNAME', 'd2d-portal-user' );
      define( 'ENV_MSTR_PASSWORD', '34A!dn@5hd' );

      // Tableau
      define( 'ENV_TABLEAU_TICKET_HOST', 'https://stagingtableau.benchmarks.gsa.gov/trusted/' );
      define( 'ENV_TABLEAU_CONTENT_HOST', 'https://staging.d2d.gsa.gov/trusted/' );    
    break;

    case 'd2d.gsa.gov':
      // Microstrategy
      define( 'ENV_MSTR_USERNAME', 'd2d-portal-user' );
      define( 'ENV_MSTR_PASSWORD', '34A!dn@5hd' );

      // Tableau
      define( 'ENV_TABLEAU_TICKET_HOST', 'https://tableau.benchmarks.gsa.gov/trusted/' );
      define( 'ENV_TABLEAU_CONTENT_HOST', 'https://d2d.gsa.gov/trusted/' );
    break;   
  endswitch;
  